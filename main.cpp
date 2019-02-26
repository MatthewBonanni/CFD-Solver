#include "Dsys.h"
#include <cmath>

double u(double t, double x, double y){return exp(y)*cos(x - t);}
double v(double t, double x, double y){return exp(y)*sin(x - t);}

int main(){
    double dt = 0.01;
    double x0 = 0;
    double y0 = -0.1;
    double tmax = 10;

    Dsys sys1 (dt, x0, y0);
    sys1.FillTvec(tmax);
    sys1.SetVel(*u, *v);
    sys1.MarchAB();
    sys1.PrintTraj();
    sys1.ExportData("data.csv");
}