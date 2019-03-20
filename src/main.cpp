#include "Dsys_Anal.h"
//#include "Dsys_Int.h"
#include "eigen/Eigen/Dense"
#include <vector>
#include <cmath>
#include <iostream>

using namespace Eigen;

void sample_1();
void sample_2();

int main(){
    sample_1();
}

// Cool looking sample
void sample_1(){

    auto u = [] (double t, double x, double y) {return y*t - x;};
    auto v = [] (double t, double x, double y) {return -x*sin(x - t);};

    double dt = 0.01;

    double tmax = 10;

    VectorXd x0(7);
    VectorXd y0(7);

    x0 << 0, 0, 0, 0, 0, 0, 0;
    y0 << 0, -0.1, -0.2, -0.3, -0.4, -0.5, -0.6;

    Dsys_Anal sys1 (dt, tmax, x0, y0, u, v);

    sys1.MarchAB();

    sys1.ExportData("data/sample_1.json");
}

// Stokes drift
void sample_2(){

    auto u = [] (double t, double x, double y) {return (0.2*M_PI)*exp(y)*cos(x-(2*M_PI)*t);};
    auto v = [] (double t, double x, double y) {return (0.2*M_PI)*exp(y)*sin(x-(2*M_PI)*t);};

    double dt = 0.01;

    double tmax = 10;

    VectorXd x0(5);
    VectorXd y0(5);
    
    x0 << 0, 0, 0, 0, 0;
    y0 << -0.1, -0.2, -0.3, -0.4, -0.5;

    Dsys_Anal sys1 (dt, tmax, x0, y0, u, v);

    sys1.MarchAB();

    sys1.ExportData("data/sample_2.json");
}