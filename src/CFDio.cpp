#include "CFDio.h"
#include "eigen/Eigen/Dense"
#include <string>
#include "cstdlib"
#include <iostream>
#include <sstream>
#include <fstream>

CFDio::CFDio(std::string path){
    SetPath(path);
}

void CFDio::SetPath(std::string path_in){
    path = path_in;
}

VectorXd CFDio::GetXData(){
    return x_data;
}

VectorXd CFDio::GetYData(){
    return y_data;
}

VectorXd CFDio::GetUData(){
    return u_data;
}

VectorXd CFDio::GetVData(){
    return v_data;
}

void CFDio::Import(){

    std::string line;
    std::vector<std::vector<double> > data;

    std::ifstream infile(path);

    double val;

    while (getline(infile, line)){

        data.push_back(std::vector<double>());

        std::istringstream ss(line);

        while(ss >> val){
            data.back().push_back(val);

            if (ss.peek() == ',') ss.ignore();
        }
    }

    int N = data.size();

    x_data.resize(N);
    y_data.resize(N);
    u_data.resize(N);
    v_data.resize(N);

    for (std::size_t i = 1; i != N; ++i){

        x_data(i) = data[i][1];
        y_data(i) = data[i][2];
        u_data(i) = data[i][3];
        v_data(i) = data[i][4];

    }
}