#include "Dsys_Int.h"
#include "json.hpp"
#include <vector>
#include "eigen/Eigen/Dense"
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <fstream>
#include <string>

using json = nlohmann::json;
using namespace Eigen;

double GridInterp(VectorXd x_data, VectorXd y_data,
                  VectorXd field_data, double x_target, double y_target);

// Class constructor
Dsys_Int::Dsys_Int(double dt, double tmax, 
                   VectorXd x0, VectorXd y0,
                   VectorXd x_data, VectorXd y_data,
                   VectorXd u_data, VectorXd v_data){

    SetTime(dt, tmax);
    SetICs(x0, y0);
    SetVel(x_data, y_data, u_data, v_data);
}

// Sets time parameters
void Dsys_Int::SetTime(double dt_in, double tmax_in){
    dt = dt_in;
    tmax = tmax_in;

    // Compute number of required steps
    t_count = (tmax / dt) + 1;

    t.resize(t_count);

    // Iterate through time vector
    for (std::size_t i = 0; i != t_count; ++i){
        t(i) = dt * i;
    }

    t_set = true;

    if (t_set && ic_set){
        ResizeParts();
    }
}

// Sets initial conditions
void Dsys_Int::SetICs(VectorXd x0, VectorXd y0){
    // Verify same quantity of x and y coords
    if (x0.size() != y0.size()){
        throw std::invalid_argument("Mismatched IC Vectors");
    }

    parts.resize(x0.size());

    // ResizeParts position vectors for all particles
    for (std::size_t n = 0; n != parts.size(); ++n){
        parts[n].x.resize(1);
        parts[n].y.resize(1);

        parts[n].x(0) = x0(n);
        parts[n].y(0) = y0(n);
    }

    ic_set = true;

    if (t_set && ic_set){
        ResizeParts();
    }
}

// Sets velocity field data
void Dsys_Int::SetVel(VectorXd x_in, VectorXd y_in,
                      VectorXd u_in, VectorXd v_in){
    x_data = x_in;
    y_data = y_in;
    u_data = u_in;
    v_data = v_in;
}

void Dsys_Int::ResizeParts(){
    // Resize position vectors of all particles
    for (std::size_t n = 0; n != parts.size(); ++n){
        parts[n].x.conservativeResize(t_count + 1);
        parts[n].y.conservativeResize(t_count + 1);
    }
}

// Marches using Explicit Euler scheme
void Dsys_Int::MarchEE(){
    // ResizeParts neighbor variables
    double u_n = 0, v_n = 0;

    // Time marching
    for (std::size_t i = 0; i != t_count; ++i){

        // Iterate through particles
        for (std::size_t n = 0; n != parts.size(); ++n){

            // Compute velocity components
            u_n = GridInterp(x_data, y_data, u_data, parts[n].x(i), parts[n].y(i));
            v_n = GridInterp(x_data, y_data, v_data, parts[n].x(i), parts[n].y(i));

            // Apply Euler
            parts[n].x(i + 1) = parts[n].x(i) + dt * u_n;
            parts[n].y(i + 1) = parts[n].y(i) + dt * v_n;
        }
    }
}

// Marches using Adams-Bashforth Scheme
void Dsys_Int::MarchAB(){
    // ResizeParts neighbor variables
    double u_n = 0, v_n = 0;

    VectorXd u_nm1(parts.size());
    VectorXd v_nm1(parts.size());

    // Time marching
    for (std::size_t i = 0; i != t_count; ++i){

        // Iterate through particles
        for (std::size_t n = 0; n != parts.size(); ++n){

            // Compute velocity components
            u_n = GridInterp(x_data, y_data, u_data, parts[n].x(i), parts[n].y(i));
            v_n = GridInterp(x_data, y_data, v_data, parts[n].x(i), parts[n].y(i));

            // Apply Euler for first step
            if (i == 0){
                parts[n].x(i + 1) = parts[n].x(i) + dt * u_n;
                parts[n].y(i + 1) = parts[n].y(i) + dt * v_n;
            }

            // Apply Adams-Bashforth
            else{
                parts[n].x(i + 1) = parts[n].x(i) + dt * ((3. / 2.) * u_n - (1. / 2.) * u_nm1(n));
                parts[n].y(i + 1) = parts[n].y(i) + dt * ((3. / 2.) * v_n - (1. / 2.) * v_nm1(n));
            }

            // Write current velocities (n) to old variables (n-1)
            u_nm1(n) = u_n;
            v_nm1(n) = v_n;
        }
    }
}

// Prints trajectory data for given particle
void Dsys_Int::PrintTraj(int n){
    // Print column headers
    printf("%6c%6c%6c\n", 't', 'x', 'y');

    // Iterate through position vectors
    for (std::size_t i = 0; i != t_count; ++i){
        printf("%6.2f%6.2f%6.2f\n", t[i], parts[n].x(i), parts[n].y(i));
    }
}

// Exports data to given file
void Dsys_Int::ExportData(std::string filename){
    // Create json object
    json j;

    // Write t vector
    j["t"] = t;

    // Create empty array for particles
    j["parts"] = json::array();
    
    // Iterate through particles
    for (std::size_t n = 0; n != parts.size(); ++n){

        // Fill json
        j["parts"][n]["x"] = parts[n].x;
        j["parts"][n]["y"] = parts[n].y;
    }

    // Write file
    std::ofstream outfile(filename);
    outfile << std::setw(4) << j << std::endl;
}

double GridInterp(VectorXd x_data, VectorXd y_data,
                  VectorXd field_data, double x_target, double y_target){

    VectorXd dx = x_data.array() - x_target;
    VectorXd dy = y_data.array() - y_target;

    VectorXd d = (dx.array().square() + dy.array().square()).sqrt();

    VectorXd::Index i1, i2, i3;

    double min = d.minCoeff(&i1);
    if (min == 0){
        return field_data(i1);
    }

    d(i1) = d.maxCoeff() + 1;
    min = d.minCoeff(&i2);
    d(i2) = d.maxCoeff() + 1;
    min = d.minCoeff(&i3);

    Vector3d P; P << x_data(i1), y_data(i1), field_data(i1);

    Vector3d PR; PR << x_data(i3) - P(0),
                       y_data(i3) - P(1),
                       field_data(i3) - P(2);
    Vector3d PQ; PQ << x_data(i2) - P(0),
                       y_data(i2) - P(1),
                       field_data(i2) - P(2);

    Vector3d n = PR.cross(PQ);

    return P(2) - (1 / n(2)) * (n(0)*(x_target - P(0)) + n(1)*(y_target - P(1)));
}