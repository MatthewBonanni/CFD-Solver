#include <vector>
#include <string>
#include <functional>

class Dsys {
        double dt;
        std::vector<double> t, x, y;
        std::function<double(double, double, double)> u;
        std::function<double(double, double, double)> v;
    public:
        Dsys(double, double, double);
        void FillTvec(double);
        void SetVel(double (*u_in)(double, double, double),
        double (*v_in)(double, double, double));
        void MarchIE();
        void MarchAB();
        double GetDt();
        void PrintTraj();
        void ExportData(std::string);
};