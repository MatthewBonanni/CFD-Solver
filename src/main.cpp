#include "Dsys_Anal.h"
#include "Dsys_Int.h"
#include "CFDio.h"
#include "eigen/Eigen/Dense"
#include <vector>
#include <cmath>
#include <iostream>

using namespace Eigen;

void sample_1();
void sample_2();
void sample_3();

int main(){
    sample_3();
}

// Cool looking sample
void sample_1(){

    auto u = [] (double t, double x, double y) {return y*t - x;};
    auto v = [] (double t, double x, double y) {return -x*sin(x - t);};

    double dt = 0.01;

    double tmax = 10;

    VectorXd x0(7); x0 << 0, 0, 0, 0, 0, 0, 0;
    VectorXd y0(7); y0 << 0, -0.1, -0.2, -0.3, -0.4, -0.5, -0.6;
    
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

    VectorXd x0(5); x0 << 0, 0, 0, 0, 0;
    VectorXd y0(5); y0 << -0.1, -0.2, -0.3, -0.4, -0.5;

    Dsys_Anal sys1 (dt, tmax, x0, y0, u, v);

    sys1.MarchAB();

    sys1.ExportData("data/sample_2.json");
}

// ANSYS cylinder cross flow
void sample_3(){
    CFDio ANSYS_data("data/ANSYS.txt");

    ANSYS_data.Import();

    VectorXd x_data = ANSYS_data.GetXData();
    VectorXd y_data = ANSYS_data.GetYData();
    VectorXd u_data = ANSYS_data.GetUData();
    VectorXd v_data = ANSYS_data.GetVData();

    double dt = 0.25;

    double tmax = 30;

    VectorXd x0(19); x0 << -0.45,
                           -0.45,
                           -0.45,
                           -0.45,
                           -0.45,
                           -0.45,
                           -0.45,
                           -0.45,
                           -0.45,
                           -0.45,
                           -0.45,
                           -0.45,
                           -0.45,
                           -0.45,
                           -0.45,
                           -0.45,
                           -0.45,
                           -0.45,
                           -0.45;
    VectorXd y0(19); y0 << -0.45,
                           -0.40,
                           -0.35,
                           -0.30,
                           -0.25,
                           -0.20,
                           -0.15,
                           -0.10,
                           -0.05,
                           0.00,
                           0.05,
                           0.10,
                           0.15,
                           0.20,
                           0.25,
                           0.30,
                           0.35,
                           0.40,
                           0.45;

    Dsys_Int sys1(dt, tmax,
                  x0, y0,
                  x_data, y_data, u_data, v_data);
    
    sys1.MarchAB();

    sys1.ExportData("data/sample_3.json");
}