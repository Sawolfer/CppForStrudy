
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class ComplexNumber{
    double a, b;

public:
    ComplexNumber(double a, double b){
        this -> a = a;
        this -> b = b;
    }

     string equal(ComplexNumber B){
        if (a == B.a && b == B.b){
            return "true\n";
        }
        return "false\n";
    }

    ComplexNumber operator+(ComplexNumber B){
        return ComplexNumber(a + B.a, b + B.b);
    }
    ComplexNumber operator-(ComplexNumber B){
        return ComplexNumber(a - B.a, b - B.b);
    }
    ComplexNumber operator*(ComplexNumber B){
        return ComplexNumber((a * B.a )-( b * B.b),(a * B.b )+( b * B.a));
    }
    ComplexNumber operator/(ComplexNumber B){
        return ComplexNumber(((a * B.a )+( b * B.b))/(B.a * B.a + B.b * B.b),((b * B.a )-( a * B.b))/(B.a * B.a + B.b * B.b));
    }
    void print(){
        if (b < 0){
            cout << fixed << setprecision(2) << a << b << "i\n";
        } else {
            cout << fixed << setprecision(2) << a << "+" << b << "i\n";
        }

    }
};

int main(){
    int n;
    cin >> n;

    for (int i = 0; i < n; i++){
        string op;
        double a, b, c, d;
        cin >> op >> a >> b >> c >> d;
        ComplexNumber complNum1(a, b);
        ComplexNumber complNum2(c, d);
        if (op == "="){
            cout << complNum1.equal(complNum2);
        } else if (op == "+"){
            ComplexNumber answer(complNum1 + complNum2);
            answer.print();
        } else if (op == "-"){
            ComplexNumber answer(complNum1 - complNum2);
            answer.print();
        } else if (op == "*"){
            ComplexNumber answer(complNum1 * complNum2);
            answer.print();
        } else if (op == "/"){
            ComplexNumber answer(complNum1 / complNum2);
            answer.print();
        }
    }

    return 0;
}

