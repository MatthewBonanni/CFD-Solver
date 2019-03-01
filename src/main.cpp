#include "Dsys.h"
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
    MatrixXd m(3,3);

    m(0,0) = 3;
    std::cout << m << std::endl;
}

void solve(){
    // Step size
    double dt = 0.01;

    // Initial conditions of particles
    std::vector<double> x0 = {0, 0, 0, 0, 0, 0, 0};
    std::vector<double> y0 = {0, -0.1, -0.2, -0.3, -0.4, -0.5, -0.6};

    // Advection duration
    double tmax = 10;

    // Construct dynamical system
    Dsys sys1 (dt, x0, y0);

    // Compute and fill time vector
    sys1.FillTvec(tmax);

    // Set velocity field
    sys1.SetVel(*u, *v);

    // March using Adams-Bashforth Scheme
    sys1.MarchAB();

    // Export data
    sys1.ExportData("data/traj.json");
}