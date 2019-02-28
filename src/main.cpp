#include "Dsys.h"
#include <vector>
#include <cmath>

// Velocity field equations
double u(double t, double x, double y){return y*t - x;}
double v(double t, double x, double y){return sin(x - t);}

int main(){
    // Step size
    double dt = 0.01;

    // Initial conditions of particles
    std::vector<double> x0 = {0, 0, 0, 0, 0};
    std::vector<double> y0 = {-0.1, -0.2, -0.3, -0.4, -0.5, };

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
    sys1.ExportData("out/data.json");
}