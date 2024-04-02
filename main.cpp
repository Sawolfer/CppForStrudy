#include <iostream>


// source https://codeforces.com/group/x7EpYPdPGy/contest/514065/problem/A
// for uml https://app.diagrams.net

using namespace std;



class PhysicalItem{
private:
    bool isUsedOnce;
    Character *owner;
    string name;

public:
    void use(Character user, Character target){
        
    }
    string getName(){
        return name;
    }
    virtual void setup(){

    }

protected:
    Character getOwner(){
        return *owner;
    }
    void  useCondition(Character user, Character target){}

    void giveDamageTo(Character to, int damage){
        
    }
    void giveHealTo(Character to, int heal){
        
    }
    void afterUse(){
        
    }
    void useLogic(Character user, Character target){}

    void print(ostream os){
        
    }

};
class Character{
    friend class PhysicalItem;

    friend ostream& operator<<(ostream &os, const Character &character){
        os << character.name << " " << character.healthPoints;
    }

private:
    int healthPoints;
    string name;

public:
    
    string getName(){
        return name;
    }
    int getHealthPoints(){
        return healthPoints;
    }

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
        
    }
    void print(ostream os){
        
    }

};
