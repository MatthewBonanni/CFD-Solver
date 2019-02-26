#include "dsys.h"

double u(double t, double x, double y){return x - y + 1;}
double v(double t, double x, double y){return 2*x - y;}

int main(){
    double dt = 0.1;
    double x0 = 0;
    double y0 = 0;
    double tmax = 10;

    dsys sys1 (dt, x0, y0);
    sys1.fill_tvec(tmax);
    sys1.set_vel(*u, *v);
    sys1.march_ie();
    sys1.printtraj();
    sys1.export_data("data.csv");
}