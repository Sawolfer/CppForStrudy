#include <iostream>
#include <vector>
#include <string>
#include <map>


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
class Container{

private:
    vector<T> elements;

public:
    Container<T>(){}
    Container<T>(const Container<T> &other){
        this -> elements = other.elements;
    }

    bool find(T item){
        return find(elements.begin(), elements.end(), item) != elements.end();
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


template<typename T>
concept DerivedFromPhysicalItem = is_base_of<PhysicalItem, T>::value;

template<DerivedFromPhysicalItem T>
class Container{

private:
    map<string, T> elements;

public:
    bool find(T item){
        return find(elements.begin(), elements.end(), item) != elements.end();
    }
    void removeItem(T newItem){
        elements.erase(newItem.getName());
    }

    void addItem(T newItem){
        elements.insert(pair<string, T>(newItem.getName(), newItem));
    }
    void addItem(T* newItem){
        elements.push_back(*newItem);
    }

    T find(string itemName){
        return elements[itemName];
    }

    void removeItem(string itemName){
        elements.erase(itemName);
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
    int getHealthPoints(){
        return healthPoints;
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
    Weapon(int damage, bool isUsedOnce, Character *owner, string name) : PhysicalItem(isUsedOnce, owner, name){
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

};


class MedicBag : public ContainerWithMaxCapacity<Potion>{
public:
    MedicBag() : ContainerWithMaxCapacity<Potion>(5){};
    MedicBag(int maxCapacity) : ContainerWithMaxCapacity<Potion>(maxCapacity){}
};

class SpellBook : public ContainerWithMaxCapacity<Spell>{
public:
    SpellBook() : ContainerWithMaxCapacity<Spell>(5){};
    SpellBook(int maxCapacity) : ContainerWithMaxCapacity<Spell>(maxCapacity){}
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

    void drink(Character target, string potionName){

    }

    void showPotions(){

    }

};

class SpellUser : public Character{
public:
    SpellUser(string name, int healthPoints) : Character(name, healthPoints){}

};

class Fighter : public  WeaponUser, public  PotionUser{
public:
    int maxAllowedWeapons = 3;
    int maxAllowedPotions = 5;

    Fighter(string name, int healthPoints) : WeaponUser(name, healthPoints, maxAllowedWeapons), PotionUser(name, healthPoints, maxAllowedPotions){

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

    Narrator narrator;
    Container<Character*> characters;
    Container<PhysicalItem*> items;
    string input;
    cin >> input;

    if (input == "Create character"){
        string type;
        cin >> type;
        if (type == "Fighter"){
            string name;
            int healthPoints;
            cin >> name;
            cin >> healthPoints;
            Fighter *fighter = new Fighter(name, healthPoints);
            characters.addItem(dynamic_cast<WeaponUser*>(fighter));
        }
        else if (type == "Wizard"){
            string name;
            int healthPoints;
            cin >> name;
            cin >> healthPoints;
            Wizard *wizard = new Wizard(name, healthPoints);
            characters.addItem(dynamic_cast<PotionUser*>(wizard));
        }
        else if (type == "Archer"){
            string name;
            int healthPoints;
            cin >> name;
            cin >> healthPoints;
            Archer *archer = new Archer(name, healthPoints);
            characters.addItem(dynamic_cast<WeaponUser*>(archer));
        }
    }


    return 0;
}
