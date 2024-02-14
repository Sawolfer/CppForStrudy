//
// Created by Савва Пономарев on 14.02.2024.
//
#include <iostream>
#include <string>

using namespace std;

class Shape{

public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;

};

class Rectangle : public Shape{
protected:
    int width;
    int height;
public:
    Rectangle(int width, int height){
        this->width = width;
        this->height = height;
    }
    double area() const override{
        return width * height;
    }

    double perimeter() const override{
        return (width + height)*2;
    }
};

class Circle : public Shape{

protected:
    double radius;
public:
    Circle(double radius){
        this->radius = radius;
    }

    double area() const override{
        return 3.14 * radius * radius;
    }
    double perimeter() const override{
        return 3.14 * radius * 2;
    }

};


int main()
{
    Rectangle rectangle(5.0, 3.0);
    Circle circle(4.0);

    Shape *shape = &rectangle;

    Shape* shape1 = const_cast<Rectangle*>(&rectangle);
    Shape* shape2 = const_cast<Circle*>(&circle);

    Rectangle* rectPtr = static_cast<Rectangle*>(shape1);

    if(typeid(*shape1) == typeid(Circle)) {
        std::cout << "shape is a Circle" << std::endl;
    } else {
        std::cout << "shape is not a Circle" << std::endl;
    }

    rectPtr = const_cast<Rectangle*>(rectPtr);

    int intValue = 42;
    double doubleValue = reinterpret_cast<double&>(intValue);

    return 0;
}