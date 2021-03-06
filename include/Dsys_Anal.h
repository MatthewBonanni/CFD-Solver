#include <vector>
#include "eigen/Eigen/Dense"
#include <string>
#include <functional>

using namespace Eigen;

class Dsys_Anal {
        struct Particle {
            VectorXd x, y;
        };

        double dt;
        double tmax;
        VectorXd t;
        int t_count;

        std::vector<Particle> parts;
        std::function<double(double, double, double)> u;
        std::function<double(double, double, double)> v;

        bool t_set = false;
        bool ic_set = false;
    public:
        Dsys_Anal() {};
        Dsys_Anal(double, double,
                  VectorXd, VectorXd,
                  double (*u_in)(double, double, double),
                  double (*v_in)(double, double, double));
        void SetTime(double, double);
        void SetICs(VectorXd, VectorXd);
        void SetVel(double (*u_in)(double, double, double),
                    double (*v_in)(double, double, double));
        void MarchEE();
        void MarchAB();
        void PrintTraj(int);
        void ExportData(std::string);
    private:
        void ResizeParts();
};