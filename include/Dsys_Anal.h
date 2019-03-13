#include <vector>
#include <string>
#include <functional>

class Dsys_Anal {
        struct Particle {
            std::vector<double> x, y;
        };

        double dt;
        double tmax;
        std::vector<double> t;
        std::vector<Particle> parts;
        std::function<double(double, double, double)> u;
        std::function<double(double, double, double)> v;

        bool t_set = false;
        bool ic_set = false;
    public:
        Dsys_Anal() {};
        Dsys_Anal(double, double,
                  std::vector<double>, std::vector<double>,
                  double (*u_in)(double, double, double),
                  double (*v_in)(double, double, double));
        void SetTime(double, double);
        void SetICs(std::vector<double>, std::vector<double>);
        void SetVel(double (*u_in)(double, double, double),
                    double (*v_in)(double, double, double));
        void MarchEE();
        void MarchAB();
        void PrintTraj(int);
        void ExportData(std::string);
    private:
        void ResizeParts();
};