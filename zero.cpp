#include <iostream>
#include <cmath>
#include <iomanip>


using namespace std;

double f(double x) {
    return sin(x);
}

double rectangularApproximation(double a, double b, int n) {
    double delta = (b - a) / n;
    double sum = 0.0;
    for (int i = 0; i < n; ++i) {
        double x = a + i * delta + delta / 2;
        sum += (double)(sin(x)) * delta;
    }
    return sum;
}

int main() {
    double a, b;
    int n;

    cin >> a >> b >> n;

    double result = rectangularApproximation(a, b, n);

    cout << fixed << setprecision(2) << result << endl;

    return 0;
}
