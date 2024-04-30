#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>

//#ifdef WIN
#define GNUPLOT_NAME "C:\\gnuplot\\bin\\gnuplot -persist"
//#else
//#define GNUPLOT_NAME "gnuplot -persist"
//#endif

using namespace std;

// Function to calculate least square approximation
void leastSquareApproximation(const vector<double>& x, const vector<double>& y, double& m, double& c) {
    double sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0, sum_x_squared = 0.0;

    for (size_t i = 0; i < x.size(); ++i) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x_squared += x[i] * x[i];
    }

    double n = static_cast<double>(x.size());
    m = (n * sum_xy - sum_x * sum_y) / (n * sum_x_squared - sum_x * sum_x);
    c = (sum_y - m * sum_x) / n;
}

using namespace std;



int main()
{
    //#ifdef WIN32
    FILE* pipe = _popen(GNUPLOT_NAME, "w");
    //#else
    //    FILE* pipe = popen(GNUPLOT_NAME, "w");
    //#endif

    // Input data
    vector<double> x = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    vector<double> y = {2.3, 3.5, 4.2, 5.0, 5.8, 6.4, 7.2, 8.1, 8.9, 9.7, 10.5, 11.2, 12.0, 12.9, 13.6};

    // Calculate least square approximation
    double m, c;
    leastSquareApproximation(x, y, m, c);


    // Create Gnuplot object
    if (pipe != NULL){


        fflush(pipe);
        //#ifdef WIN32
        _pclose(pipe);
        //#else
        //        pclose(pipe);
        //#endif
    }

    // Set labels and title


    return 0;
}