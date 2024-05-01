#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include <cstdio>

using namespace std;


//#ifdef WIN
#define GNUPLOT_NAME "C:\\gnuplot\\bin\\gnuplot -persist"
//#else
#define GNUPLOT_NAME "gnuplot -persist"
// #define GNUPLOT_NAME "/opt/homebrew/Cellar/gnuplot/6.0.0/bin/gnuplot -persist"
//#endif


int main()
{

    //#ifdef WIN32
    // FILE* pipe = _popen(GNUPLOT_NAME, "w");
    //#else
    FILE* pipe = popen(GNUPLOT_NAME, "w");
    //#endifint 

    int numV0, numK0;
    double a1, b1, a2, b2;
    double v, k;

    double T, N;

    cin >> numV0 >> numK0;
    cin >> a1 >> b1;
    cin >> a2 >> b2;
    cin >> T;
    cin >> N;

    double v0, k0;

    v0 = numV0 - (a2 / b2);
    k0 = numK0 - (a1 / b1);

    vector<double> ts;
    vector<double> vs;
    vector<double> ks;

    // cout << T / N;

    for (double t = 0; t <= T; t += T/N){
        ts.push_back(t);
        v =(v0 * cos(sqrt(a1 * a2) * t)) - (k0 * ((sqrt(a2) * b1)/(b2 * sqrt(a1))) * sin(sqrt(a1 * a2) * t));
        k = (v0 * ((sqrt(a1) * b2) / (b1 * sqrt(a2))) * sin(sqrt(a1 * a2) * t) + (k0 * cos(sqrt(a1 * a2) * t)));

        v += a2/b2;
        k += a1/b1;

        vs.push_back(v);
        ks.push_back(k);
    }

    cout << "t:\n";
    for (int i = 0; i < ts.size(); i++){
        cout << fixed << setprecision(2) << ts[i] << " ";
    }
    cout << endl;

    cout << "v:\n";
    for (int i = 0; i < vs.size(); i++){
        cout << fixed << setprecision(2) << vs[i] << " ";
    }

    cout << endl;

    cout << "k:\n";
    for (int i = 0; i < ks.size(); i++){
        cout << fixed << setprecision(2) << ks[i] << " ";
    }
    
    if (pipe != NULL) {
        string graphic = "";

        fprintf(pipe, "set xlabel 'Prey'\n");
        fprintf(pipe, "set ylabel 'Predator'\n");

        fprintf(pipe, "plot '-' with lines title 'v(t) & k(t)', '-' with lines title 'v(k)'\n");

        for (int i = 0; i < ts.size(); i++) {
            fprintf(pipe, "%f %f\n", ts[i], vs[i]);
        }
        fprintf(pipe, "e\n");

        for (int i = 0; i < ts.size(); i++) {
            fprintf(pipe, "%f %f\n", ks[i], vs[i]);
        }
        fprintf(pipe, "e\n");

        fflush(pipe);
        fprintf(pipe, "exit\n");
        pclose(pipe);
    }


    return 0;
}
