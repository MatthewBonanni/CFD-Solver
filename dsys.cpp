#include "dsys.h"
#include <cstdio>
#include <fstream>
#include <string>

dsys::dsys(double dt_in, double x0, double y0){
    dt = dt_in;

    x.resize(1);
    y.resize(1);

    x[0] = x0;
    y[0] = y0;
}

void dsys::fill_tvec(double tmax){
	// Compute number of required steps
	float N = (tmax / dt) + 1;

    t.resize(N);
    x.resize(N+1);
    y.resize(N+1);

	// Iterate through time vector
	for (auto it = t.begin(); it != t.end(); ++it){
		auto i = std::distance(t.begin(), it);

		*it = dt * i;
	}
}

void dsys::march_ie(){
    // Initialize neighbor variables
	double u_n = 0, v_n = 0;

	// Time marching
	for (std::size_t i = 0; i != t.size(); ++i){

		// Compute velocity components
		u_n = x[i] - y[i] + 1;
		v_n = 2 * x[i] - y[i];

		// Apply Euler
		x[i+1] = x[i] + dt * u_n;
		y[i+1] = y[i] + dt * v_n;
	}
}

void dsys::march_ab(){
    // Initialize neighbor variables
	double u_n = 0, v_n = 0;
	double u_nm1 = 0, v_nm1 = 0;

	// Time marching
	for (std::size_t i = 0; i != t.size(); ++i){

		// Compute velocity components
		u_n = x[i] - y[i] + 1;
		v_n = 2 * x[i] - y[i];

		// Apply Euler for first step
		if (i == 1){
			x[i+1] = x[i] + dt * u_n;
			y[i+1] = y[i] + dt * v_n;
		}

		// Apply Adams-Bashforth
		else {
			x[i+1] = x[i] + dt * ((3./2.) * u_n - (1./2.) * u_nm1);
			y[i+1] = y[i] + dt * ((3./2.) * v_n - (1./2.) * v_nm1);
		}

		// Write current velocities (n) to old variables (n-1)
		u_nm1 = u_n;
		v_nm1 = v_n;
	}
}

double dsys::getdt(){
    return dt;
}

void dsys::printtraj(){
    printf("%6c%6c%6c\n", 't', 'x', 'y');
    for (std::size_t i = 0; i != t.size(); ++i){
        printf("%6.2f%6.2f%6.2f\n", t[i], x[i], y[i]);
    }
}

void dsys::export_data(std::string filename){
    std::ofstream outfile;
	outfile.open(filename);

	// Write headers
	outfile << "t,x,y\n";

	// Iterate through trajectory data, write each line
	for (std::size_t i = 0; i != t.size(); ++i){
		outfile << std::to_string(t[i]) << ","
				<< std::to_string(x[i]) << ","
				<< std::to_string(y[i]) << "\n";
	}

	outfile.close();
}