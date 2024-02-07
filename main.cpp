#include <iostream>
#include <string>
#include "list"


using namespace std;

class Animal{

public:
    Animal(string n) : name(name){};
    string name;
    int age;
    virtual void makeSound() {
        cout << "sound";
    }
};

class LandAnimal : virtual public Animal{
public:
    LandAnimal(string name): Animal(name){};

    virtual void walk(){}
};

class WaterAnimal : virtual public Animal{
public:
    WaterAnimal(string name) : Animal(name){};

    virtual void swim(){}
};

class Lion : public LandAnimal{
public:
    Lion(string name) : Animal(name), LandAnimal(name){}
    void makeSound() override{
        cout << "Rar\n";
    }

};

class Dolphin : public WaterAnimal{
public:
    Dolphin(string name) : Animal(name), WaterAnimal(name){};
    void makeSound() override{
        cout << "Bloop\n";
    }
};

class Frog : public LandAnimal, WaterAnimal{
public:
    Frog(string name) : WaterAnimal(name), LandAnimal(name), Animal(name){};
    void makeSound() override{
        cout << "Kwa \n";
    }
};


int main() {

    Animal *animals[3];

    Lion lion("Bee");
    Dolphin dolphin("Wave");
    Frog frog("Shrek");

    animals[0] = &lion;
    animals[1] = &dolphin;
    animals[2] = &frog;

    for(Animal *animal : animals){
        animal->makeSound();
    }

    return 0;
}