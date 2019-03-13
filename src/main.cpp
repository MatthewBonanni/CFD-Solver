#include "Dsys_Anal.h"
#include "eigen/Eigen/Dense"
#include <vector>
#include <cmath>
#include <iostream>

using namespace Eigen;

// Stokes drift
/*
double w = 2 * M_PI;
double k = 1;
double a = 0.1;

double u(double t, double x, double y){return (w*a*k)*exp(k*y)*cos(k*x-w*t);}
double v(double t, double x, double y){return (w*a*k)*exp(k*y)*sin(k*x-w*t);}
*/

// Velocity field equations
double u(double t, double x, double y){return y*t - x;}
double v(double t, double x, double y){return -x*sin(x - t);}

void solve();

int main(){
    solve();
}

void solve(){
    // Step size
    double dt = 0.01;

    // Advection duration
    double tmax = 10;

    // Initial conditions of particles
    std::vector<double> x0 = {0, 0, 0, 0, 0, 0, 0};
    std::vector<double> y0 = {0, -0.1, -0.2, -0.3, -0.4, -0.5, -0.6};

    // Construct dynamical system
    Dsys_Anal sys1 (dt, tmax, x0, y0, *u, *v);

    // March using Adams-Bashforth Scheme
    sys1.MarchAB();

    // Export data
    sys1.ExportData("data/traj.json");
}