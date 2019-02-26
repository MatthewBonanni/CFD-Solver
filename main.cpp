#include "dsys.h"
#include <cmath>

double u(double t, double x, double y){return exp(y)*cos(x - t);}
double v(double t, double x, double y){return exp(y)*sin(x - t);}

int main(){
    double dt = 0.01;
    double x0 = 0;
    double y0 = -0.1;
    double tmax = 10;

    dsys sys1 (dt, x0, y0);
    sys1.fill_tvec(tmax);
    sys1.set_vel(*u, *v);
    sys1.march_ab();
    sys1.printtraj();
    sys1.export_data("data.csv");
}