#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

//#ifdef WIN
#define GNUPLOT_NAME "C:\\gnuplot\\bin\\gnuplot -persist"
//#else
//#define GNUPLOT_NAME "gnuplot -persist"
//#endif


int main()
{

    //#ifdef WIN32
    FILE* pipe = _popen(GNUPLOT_NAME, "w");
    //#else
    //    FILE* pipe = popen(GNUPLOT_NAME, "w");
    //#endif

    int N = 100;
    double x0 = 0.0;
    double xN = 3.14;
    double h = (xN - x0) / (N - 1);
    double* x = new double[N];
    double* y = new double[N];
    for (int i = 0; i < N; i++)
    {
        x[i] = x0 + i * h;
        y[i] = sin(x[i]);
    }
    string function = "";
    if (pipe != NULL)
    {
        fprintf(pipe, "plot '-' with points title 'data points' pointtype 5, %s with lines title "
                      "'approximation' linetype 1\n", function.c_str());
        fprintf(pipe, "%f %f", 0.1, 0.2);

        fprintf(pipe, "%s\n", "plot '-' using 1:2 title 'sin' with lines");
        for (int i = 0; i < N; i++)
            fprintf(pipe, "%f\t%f\n", x[i], y[i]);

        fprintf(pipe, "%s\n", "e");
        fflush(pipe);
        //#ifdef WIN32
        _pclose(pipe);
        //#else
        //        pclose(pipe);
        //#endif
    }
}

