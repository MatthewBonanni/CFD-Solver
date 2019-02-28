#include <vector>
#include <string>
#include <functional>

class Dsys {
        double dt;
        std::vector<double> t;
        struct Particle {
            std::vector<double> x, y;
        };
        std::vector<Particle> parts;
        std::function<double(double, double, double)> u;
        std::function<double(double, double, double)> v;
    public:
        Dsys() {};
        Dsys(double, std::vector<double>, std::vector<double>);
        void FillTvec(double);
        void SetVel(double (*u_in)(double, double, double),
        double (*v_in)(double, double, double));
        void MarchEE();
        void MarchAB();
        double GetDt();
        void PrintTraj(int);
        void ExportData(std::string);
};