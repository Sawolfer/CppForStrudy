//
// Created by Савва Пономарев on 31.01.2024.
//

#include "iostream"
#include "string"

using namespace std;




static class Box{

    unsigned int length;
    unsigned int width;
    unsigned int weight;

    string volume = "boom";


public:
    Box(){
        length = 10;
        width = 5;
        weight = 11;
    }
    Box(Box & box){
        length = box.length;
        width = box.width;
        weight = box.weight;
    }
    Box(int a, int b, int c){
        length = a;
        weight = b;
        width = c;
    }

    int operator+ (Box box){
        length += box.length;
        weight += box.weight;
        width += box.width;
    }
    void display(){
        std::cout << length << " " << weight << " " << width;
    }

    string getVolume(){
        return volume;
    }
    void scale(unsigned scaleValue){
        length *= scaleValue;
        weight *= scaleValue;
        width *= scaleValue;
    }
    bool isBigger(Box other){
        if (length < other.length && weight < other.weight && width < other.width) {
            return false;
        }
        return true;
    }
    bool isSmaller(Box other){
        if (length < other.length && weight < other.weight && width < other.width) {
            return true;
        }
        return false;
    }
    int operator* (int scale){
        length*= scale;
        weight *= scale;
        width *= scale;
    }
    bool operator= (Box other){
        if (length == other.length && weight == other.weight && width == other.width){
            return true;
        }
        return false;
    }
};

static class Cube{
    int length;



public:
    Cube(int l){
        length = l;
    }
    Box  toBox(){
        Box box(length, length, length);
        return box;
    }

};

int main(){

    Cube cube(3);

//    Box box(cube.toBox());

    return 0;
}
