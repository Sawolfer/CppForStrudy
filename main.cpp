#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>
#include <sstream>


// source https://codeforces.com/group/x7EpYPdPGy/contest/514065/problem/A
// for uml https://app.diagrams.net

using namespace std;

class Character;

class PhysicalItem{
private:
    bool isUsedOnce;
    Character *owner;
    string name;

public:

    PhysicalItem(bool isUsedOnce, Character *owner, string name){
        this -> isUsedOnce = isUsedOnce;
        this -> owner = owner;
        this -> name = name;
    }
    PhysicalItem(){}
    PhysicalItem(const PhysicalItem &other){
        this -> isUsedOnce = other.isUsedOnce;
        this -> owner = other.owner;
        this -> name = other.name;
    }

    void use(const Character& user, const Character& target){

    }
    string getName(){
        return name;
    }
    virtual void setup(){

    }
    ~PhysicalItem() = default;

protected:
    Character& getOwner(){
        return *owner;
    }
    void  useCondition(const Character& user, const Character& target){}

    void giveDamageTo(const Character& to, int damage){

    }
    void giveHealTo(const Character& to, int heal){

    }
    void afterUse(){

    }
    void useLogic(const Character& user, const Character& target){}

    void print(ostream os){

    }

};

template<typename T>
concept DerivedFromPhysicalItem = is_base_of<PhysicalItem, T>::value;

template<typename T>
class Container{

private:
    vector<T> elements;

public:
    Container<T>(){}
    Container<T>(const Container<T> &other){
        this -> elements = other.elements;
    }

    T find(string itemName){
        for (int i = 0; i < elements.size(); i++){
            if ((elements[i] -> getName()) == itemName){
                return elements[i];
            }
        }
    }

    void removeItem(T newItem){
        elements.erase(newItem);
    }
    void addItem(T newItem){
        elements.push_back(newItem);
    }
    void addItem(T* newItem){
        elements.push_back(*newItem);
    }

    void deleteAllItems(){
        elements.clear();
    }

    ~Container() = default;
};

template<DerivedFromPhysicalItem T>
class Container<T>{

private:
    map<string, T> elements;

public:

    void removeItem(T newItem){
        elements.erase(newItem.getName());
    }

    void addItem(T newItem){
        elements.insert(pair<string, T>(newItem.getName(), newItem));
    }
    void addItem(T* newItem){
        elements.insert(pair<string, T>(newItem->getName(), *newItem));
    }

    T find(string itemName){
        return elements[itemName];
    }

    void removeItem(string itemName){
        elements.erase(itemName);
    }

    void deleteAllItems(){
        elements.clear();
    }

    ~Container() = default;
};


class Character{
    friend class PhysicalItem;

    friend ostream& operator<<(ostream &os, const Character &character){
        os << character.name << " " << character.healthPoints;
    }

private:
    int healthPoints;
    string name;
    bool died = false;

    Container<PhysicalItem> items;

public:
    Character(string name, int healthPoints){
        this -> name = name;
        this -> healthPoints = healthPoints;
    }
    Character(){}
    Character(const Character &other){
        this -> name = other.name;
        this -> healthPoints = other.healthPoints;
    }

    string getName(){
        return name;
    }
    bool getDied(){
        return died;
    }
    int getHealthPoints(){
        return healthPoints;
    }

    void onDamage(int damage){
        takeDamage(damage);
        if (healthPoints <= 0){
            onDie();
        }
    }
    void onHeal(int heal){
        healthPoints += heal;
    }

    void addItem(PhysicalItem *item){
        items.addItem(item);
    }

    void onDie(){
        items.deleteAllItems();
        delete this;
    }

    ~Character() = default;

private:
    void takeDamage(int damage){
        healthPoints -= damage;
    }
    void heal(int heal){
        healthPoints += heal;
    }

protected:
    void obtainItemSideEffect(PhysicalItem *item){

    }

    void loseItemSideEffect(PhysicalItem *item){
        items.deleteAllItems();
    }
    void print(ostream os){

    }
};

//############
// CONTAINERS
//############

template<typename T>
class ContainerWithMaxCapacity : public Container<T>{
private:
    int maxCapacity;

public:
    ContainerWithMaxCapacity(int maxCapacity){
        this -> maxCapacity = maxCapacity;
    }
    void addItem(T item){
        Container<T>::addItem(item);
    }
    void show(){

    }
};

//############
//   ITEMS
//############

class Weapon: public PhysicalItem{
private:
    int damage;
public:
    Weapon(int damage, Character *owner, string name) : PhysicalItem(false, owner, name){
        this -> damage = damage;
    }
    int getDamage(){
        return damage;
    }
    void setup(){

    }
private:
    void useLogic(Character user, Character target){

    }
protected:
    void print(ostream os){

    }
};

class Potion: public PhysicalItem{
private:
    int heal;
public:
    Potion(int heal, bool isUsedOnce, Character *owner, string name) : PhysicalItem(isUsedOnce, owner, name){
        this -> heal = heal;
    }
    int getHeal(){
        return heal;
    }
    void setup(){

    }
private:
    void useLogic(Character user, Character target){

    }
protected:
    void print(ostream os){

    }
};

class Spell: public PhysicalItem{
private:
    vector<Character*> allowedTargets ;
public:

    Spell(bool isUsedOnce, Character *owner, string name) : PhysicalItem(isUsedOnce, owner, name){

    }
    int getNumberOfAllowedTargets(){
        return allowedTargets.size();
    }
    void setup(){

    }
private:
    void useLogic(Character user, Character target){

    }
protected:
    void print(ostream os){

    }
};


class Arsenal : public ContainerWithMaxCapacity<Weapon>{
public:
    Arsenal() : ContainerWithMaxCapacity<Weapon>(3){};
    Arsenal(int maxCapacity) : ContainerWithMaxCapacity<Weapon>(maxCapacity){}

    void addWeapon(Weapon weapon){
        Container<Weapon>::addItem(weapon);
    }

    

    Weapon getWeapon(string weaponName){
        return Container<Weapon>::find(weaponName);
    }
};


class MedicBag : public ContainerWithMaxCapacity<Potion>{
public:
    MedicBag() : ContainerWithMaxCapacity<Potion>(5){};
    MedicBag(int maxCapacity) : ContainerWithMaxCapacity<Potion>(maxCapacity){}

    void addPotion(Potion potion){
        Container<Potion>::addItem(potion);
    }
};


class SpellBook : public ContainerWithMaxCapacity<Spell>{
public:
    SpellBook() : ContainerWithMaxCapacity<Spell>(5){};
    SpellBook(int maxCapacity) : ContainerWithMaxCapacity<Spell>(maxCapacity){}

    void addSpell(Spell spell){
        Container<Spell>::addItem(spell);
    }
};


//############
// CHARACTERS
//############

class WeaponUser : public Character{

protected:
    Arsenal arsenal;

public:
    WeaponUser(string name, int healthPoints, int maxAllowedWeapons) : Character(name, healthPoints){
        arsenal = Arsenal(maxAllowedWeapons);
    }

    void addWEapon(Weapon weapon){
        arsenal.addWeapon(weapon);
    }

    void attack(Character target, string weaponName){
        
    }
    void showWeapons(){

    }


};

class PotionUser : public Character{
protected:
    MedicBag bag;

public:
    PotionUser(string name, int healthPoints, int maxAllowedPotions) : Character(name, healthPoints){
        bag = MedicBag(maxAllowedPotions);
    }

    void addPotion(Potion potion){
        bag.addPotion(potion);
    }

    void drink(Character target, string potionName){

    }

    void showPotions(){

    }

};

class SpellUser : public Character{
protected:
    SpellBook book;

public:
    SpellUser(string name, int healthPoints) : Character(name, healthPoints){}

    void addSpell(Spell spell){
        book.addSpell(spell);
    }
};

class Fighter : public  WeaponUser, public  PotionUser{
public:
    int maxAllowedWeapons = 3;
    int maxAllowedPotions = 5;

    
    Fighter(string name, int healthPoints) : WeaponUser(name, healthPoints, maxAllowedWeapons), PotionUser(name, healthPoints, maxAllowedPotions){

    }

    void attack(Character target, string weaponName){
        Weapon weapon = arsenal.getWeapon(weaponName);
        target.onDamage(weapon.getDamage());
    }

    string show(){
        string message = WeaponUser::getName() + ":fighter:" + to_string(WeaponUser::getHealthPoints());
        return message;
    }


private:
    void print(ostream os){

    }
    void obtainItemSideEffect(PhysicalItem item){

    }
    void loseItemSideEffect(PhysicalItem item){
    }
};

class Archer: public WeaponUser, public PotionUser, public SpellUser{
public:
    int maxAllowedWeapons = 2;
    int maxAllowedPotions = 3;
    int maxAllowedSpells = 2;

    Archer(string name, int healthPoints) : WeaponUser(name, healthPoints, maxAllowedWeapons), PotionUser(name, healthPoints, maxAllowedPotions), SpellUser(name, healthPoints){

    }

private:
    void print(ostream os){

    }
    void obtainItemSideEffect(PhysicalItem item){

    }
    void loseItemSideEffect(PhysicalItem item){

    }
};

class Wizard: public PotionUser, public SpellUser{
public:
    int maxAllowedPotions = 10;
    int maxAllowedSpells = 10;

    Wizard(string name, int healthPoints) : PotionUser(name, healthPoints, maxAllowedPotions), SpellUser(name, healthPoints){

    }
private:
    void print(ostream os){

    }
    void obtainItemSideEffect(PhysicalItem item){

    }
    void loseItemSideEffect(PhysicalItem item){

    }
};

class Narrator: public Character{
public:
    Narrator(){

    }
    void tell(string message){
        cout << message << endl;
    }

};

int main(){

    ifstream input = ifstream("input.txt");
    ofstream output = ofstream("output.txt");
    
    Narrator narrator;
    Container<Character*> characters;
    Container<PhysicalItem*> items;
    
    string line;
    getline(input, line);
    int continueLoop = stoi(line);

    while (getline(input, line)){
        
        vector<string> words;
        istringstream iss(line);
        while (iss >> line){
            words.push_back(line);
        }
        if (words[0] == "Dialogue"){
            string name = words[1];
            int num = stoi(words[2]);
            output << name << ": " ;
            for (int i = 0; i < num; i++){
                output << words[i + 3] << " ";
            }
            output << endl;
        }

        if (words[0] == "Create"){
            if (words[1] == "character"){
                if (words[2] == "fighter"){
                    string name = words[3];
                    int healthPoints = stoi(words[4]);
                    healthPoints = stoi(line);
                    Fighter *fighter = new Fighter(name, healthPoints);
                    characters.addItem(dynamic_cast<WeaponUser*>(fighter));
                    output << "The new character fighter came to town, " << name << "." << endl;
                }
                else if (words[2] == "wizard"){
                    string name = words[3];
                    int healthPoints = stoi(words[4]);
                    healthPoints = stoi(line);
                    Wizard *wizard = new Wizard(name, healthPoints);
                    characters.addItem(dynamic_cast<PotionUser*>(wizard));
                    output << "The new character wizard came to town, " << name << "." << endl;
                }
                else if (words[2] == "archer"){
                    string name = words[3];
                    int healthPoints = stoi(words[4]);
                    healthPoints = stoi(line);
                    Archer *archer = new Archer(name, healthPoints);
                    characters.addItem(dynamic_cast<WeaponUser*>(archer));
                    output << "The new character archer came to town, " << name << "." << endl;
                }
            }
            else if (words[1] == "item"){
                if (words[2] == "weapon"){
                    string ownerName = words[3];
                    string name = words[4];
                    int damage = stoi(words[5]);
                    Character *owner = characters.find(ownerName);
                    Weapon *weapon = new Weapon(damage, owner, name);
                    owner -> addItem(weapon);
                    items.addItem(weapon);
                    output << ownerName << " just obtained a new weapon called " << name << "." << endl;
                }
                if (words[2] == "spell"){
                    string ownerName = words[3];
                    string name = words[4];
                    int damage = stoi(words[5]);
                    Character *owner = characters.find(ownerName);
                    Spell *spell = new Spell(false, owner, name);
                    owner -> addItem(spell);
                    items.addItem(spell);
                    output << ownerName << " just obtained a new spell called " << name << "." << endl;
                }
                if (words[2] == "potion"){
                    string ownerName = words[3];
                    string name = words[4];
                    int heal = stoi(words[5]);
                    Character *owner = characters.find(ownerName);
                    Potion *potion = new Potion(heal, false, owner, name);
                    owner -> addItem(potion);
                    items.addItem(potion);
                    output << ownerName << " just obtained a new potion called " << name << "." << endl;
                }
            }
        }
        
        if (words[0] == "Attack"){
            string name = words[1];
            string targetName = words[2];
            string weaponName = words[3];
            Character *user = characters.find(name);
            Character *target = characters.find(targetName);
            static_cast<WeaponUser*>(user) -> attack(*target, weaponName);
            output << name << " attacked " << targetName << " with their " << weaponName << "." << endl;
            if (target -> getDied()){
                output << targetName << " has died..." << endl;
            }
        }




    }

    return 0;
}
