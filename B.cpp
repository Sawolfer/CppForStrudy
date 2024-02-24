#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// class Compex number that realise all necessary methods
class ComplexNumber
{
    // variables that complex number consist
    double a, b;

public:
    // constructor of complex number
    ComplexNumber(double a, double b)
    {
        this->a = a;
        this->b = b;
    }
    // method that check equality of two complex numbers
    string equal(ComplexNumber B)
    {
        if (a == B.a && b == B.b)
        {
            return "true\n";
        }
        return "false\n";
    }
    // override operator of addition
    ComplexNumber operator+(ComplexNumber B)
    {
        return ComplexNumber(a + B.a, b + B.b);
    }
    // override operator of subtraction
    ComplexNumber operator-(ComplexNumber B)
    {
        return ComplexNumber(a - B.a, b - B.b);
    }
    // override operator of multiplication
    ComplexNumber operator*(ComplexNumber B)
    {
        return ComplexNumber((a * B.a) - (b * B.b), (a * B.b) + (b * B.a));
    }
    // override operator of division
    ComplexNumber operator/(ComplexNumber B)
    {
        return ComplexNumber(((a * B.a) + (b * B.b)) / (B.a * B.a + B.b * B.b), ((b * B.a) - (a * B.b)) / (B.a * B.a + B.b * B.b));
    }
    // method for output complex number
    void print()
    {
        if (b < 0)
        {
            cout << fixed << setprecision(2) << a << b << "i\n";
        }
        else
        {
            cout << fixed << setprecision(2) << a << "+" << b << "i\n";
        }
    }
};
// the main method
int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        // reading input data and initializing complex numbers
        string op;
        double a, b, c, d;
        cin >> op >> a >> b >> c >> d;
        ComplexNumber complNum1(a, b);
        ComplexNumber complNum2(c, d);
        // invoking methods, dependonsing sign in the beginning of string
        if (op == "=")
        {
            cout << complNum1.equal(complNum2);
        }
        else if (op == "+")
        {
            ComplexNumber answer(complNum1 + complNum2);
            answer.print();
        }
        else if (op == "-")
        {
            ComplexNumber answer(complNum1 - complNum2);
            answer.print();
        }
        else if (op == "*")
        {
            ComplexNumber answer(complNum1 * complNum2);
            answer.print();
        }
        else if (op == "/")
        {
            ComplexNumber answer(complNum1 / complNum2);
            answer.print();
        }
    }

    return 0;
}
