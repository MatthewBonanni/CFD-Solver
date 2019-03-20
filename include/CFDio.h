#include "eigen/Eigen/Dense"
#include <string>

using namespace Eigen;

class CFDio {
        std::string path;

        VectorXd x_data;
        VectorXd y_data;
        VectorXd u_data;
        VectorXd v_data;
    public:
        CFDio() {};
        CFDio(std::string);
        void SetPath(std::string);
        VectorXd GetXData();
        VectorXd GetYData();
        VectorXd GetUData();
        VectorXd GetVData();
        void Import();
};