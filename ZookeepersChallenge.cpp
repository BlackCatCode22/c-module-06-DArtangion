#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <stdexcept>

using namespace std;

class Animal {
public:
    string name, species, sex, arrivalDate, birthdate, uniqueID;
    double weight;
    int age;

    Animal(string sp, string n, int a, string bd, double w, string o, string arr)
        : species(sp), name(n), age(a), birthdate(bd), weight(w), arrivalDate(arr) {
        uniqueID = species + "_" + to_string(rand() % 1000 + 1); // Random ID
    }

    virtual void display() const = 0; // Pure virtual function
};

class Hyena : public Animal {
public:
    Hyena(string n, int a, string bd, double w, string o, string arr)
        : Animal("Hyena", n, a, bd, w, o, arr) {}

    void display() const override {
        cout << "Hyena: " << uniqueID << "; " << name << "; birth date "
             << birthdate << "; " << weight << " pounds; arrived " << arrivalDate << endl;
    }
};

class Lion : public Animal {
public:
    Lion(string n, int a, string bd, double w, string o, string arr)
        : Animal("Lion", n, a, bd, w, o, arr) {}

    void display() const override {
        cout << "Lion: " << uniqueID << "; " << name << "; birth date "
             << birthdate << "; " << weight << " pounds; arrived " << arrivalDate << endl;
    }
};

class Tiger : public Animal {
public:
    Tiger(string n, int a, string bd, double w, string o, string arr)
        : Animal("Tiger", n, a, bd, w, o, arr) {}

    void display() const override {
        cout << "Tiger: " << uniqueID << "; " << name << "; birth date "
             << birthdate << "; " << weight << " pounds; arrived " << arrivalDate << endl;
    }
};

class Bear : public Animal {
public:
    Bear(string n, int a, string bd, double w, string o, string arr)
        : Animal("Bear", n, a, bd, w, o, arr) {}

    void display() const override {
        cout << "Bear: " << uniqueID << "; " << name << "; birth date "
             << birthdate << "; " << weight << " pounds; arrived " << arrivalDate << endl;
    }
};

class Zoo {
public:
    vector<Animal*> animals;
    map<string, vector<string>> speciesNames;

    ~Zoo() {
        for (Animal* animal : animals) delete animal;
    }

    void readAnimalNames(const string& namesFile) {
        ifstream inFile(namesFile);
        if (!inFile) throw runtime_error("Unable to open file: " + namesFile);
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string species, name;
            getline(ss, species, ';');
            getline(ss, name);
            speciesNames[species].push_back(name);
        }
    }

    void readAnimals(const string& animalFile) {
        ifstream inFile(animalFile);
        if (!inFile) throw runtime_error("Unable to open file: " + animalFile);
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);

            int age;
            string birthdate, color, weightStr, origin, arrivalDate;

            getline(ss, line, ','); age = stoi(line.substr(0, line.find(" year")));
            getline(ss, birthdate, ','); birthdate = birthdate.substr(6);
            getline(ss, color, ','); // color
            getline(ss, weightStr, ','); double weight = stod(weightStr.substr(1));
            getline(ss, origin, ','); origin = origin.substr(6);
            getline(ss, arrivalDate, ','); arrivalDate = arrivalDate.substr(10);

            Animal* animal = nullptr;
            if (line.find("hyena") != string::npos) animal = new Hyena(speciesNames["Hyena"].back(), age, birthdate, weight, origin, arrivalDate);
            else if (line.find("lion") != string::npos) animal = new Lion(speciesNames["Lion"].back(), age, birthdate, weight, origin, arrivalDate);
            else if (line.find("tiger") != string::npos) animal = new Tiger(speciesNames["Tiger"].back(), age, birthdate, weight, origin, arrivalDate);
            else if (line.find("bear") != string::npos) animal = new Bear(speciesNames["Bear"].back(), age, birthdate, weight, origin, arrivalDate);

            if(animal) {
                speciesNames[animal->species].pop_back(); // Remove used name
                animals.push_back(animal);
            }
        }
    }

    void displayAnimals() const {
        for (const auto& animal : animals) animal->display();
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed for unique IDs
    Zoo zoo;

    try {
        zoo.readAnimalNames("animalNames.txt");
        zoo.readAnimals("arrivingAnimals.txt");
        zoo.displayAnimals();
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
    }

    return 0;
}