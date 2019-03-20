#include <vector>
#include "eigen/Eigen/Dense"
#include <string>
#include <functional>

using namespace Eigen;

class Dsys_Int {
        struct Particle {
            VectorXd x, y;
        };

        double dt;
        double tmax;
        VectorXd t;
        int t_count;

        std::vector<Particle> parts;
        VectorXd x_data;
        VectorXd y_data;
        VectorXd u_data;
        VectorXd v_data;

        bool t_set = false;
        bool ic_set = false;
    public:
        Dsys_Int() {};
        Dsys_Int(double, double,
                 VectorXd, VectorXd,
                 VectorXd, VectorXd,
                 VectorXd, VectorXd);
        void SetTime(double, double);
        void SetICs(VectorXd, VectorXd);
        void SetVel(VectorXd, VectorXd,
                    VectorXd, VectorXd);
        void MarchEE();
        void MarchAB();
        void PrintTraj(int);
        void ExportData(std::string);
    private:
        void ResizeParts();
};