#include "Dsys.hpp"
#include "json.hpp"
#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <fstream>
#include <string>

using json = nlohmann::json;

// Class constructor
Dsys::Dsys(double dt_in, std::vector<double> x0, std::vector<double> y0){
    dt = dt_in;

	// Verify same quantity of x and y coords
	if (x0.size() != y0.size()){
		throw std::invalid_argument("Mismatched IC Vectors");
	}

	parts.resize(x0.size());

	// Initialize position vectors for all particles
	for (std::size_t n = 0; n != parts.size(); ++n){
		parts[n].x.resize(1);
		parts[n].y.resize(1);

		parts[n].x[0] = x0[n];
		parts[n].y[0] = y0[n];
	}
}

// Computes and fills time vector
void Dsys::FillTvec(double tmax){
	// Compute number of required steps
	int N = (tmax / dt) + 1;

    t.resize(N);

	// Resize position vectors of all particles
	for (std::size_t n = 0; n != parts.size(); ++n){
		parts[n].x.resize(N + 1);
		parts[n].y.resize(N + 1);
	}

	// Iterate through time vector
	for (auto it = t.begin(); it != t.end(); ++it){
		auto i = std::distance(t.begin(), it);

		*it = dt * i;
	}
}

// Sets velocity field equations
void Dsys::SetVel(double (*u_in)(double, double, double),
				  double (*v_in)(double, double, double)){
	u = *u_in;
	v = *v_in;
}

// Marches using Explicit Euler scheme
void Dsys::MarchEE(){
    // Initialize neighbor variables
	double u_n = 0, v_n = 0;

	// Time marching
	for (std::size_t i = 0; i != t.size(); ++i){

		// Iterate through particles
		for (std::size_t n = 0; n != parts.size(); ++n){

			// Compute velocity components
			u_n = u(t[i], parts[n].x[i], parts[n].y[i]);
			v_n = v(t[i], parts[n].x[i], parts[n].y[i]);

			// Apply Euler
			parts[n].x[i + 1] = parts[n].x[i] + dt * u_n;
			parts[n].y[i + 1] = parts[n].y[i] + dt * v_n;
		}
	}
}

// Marches using Adams-Bashforth Scheme
void Dsys::MarchAB(){
    // Initialize neighbor variables
	double u_n = 0, v_n = 0;
	double u_nm1 = 0, v_nm1 = 0;

	// Time marching
	for (std::size_t i = 0; i != t.size(); ++i){

		// Iterate through particles
		for (std::size_t n = 0; n != parts.size(); ++n){

			// Compute velocity components
			u_n = u(t[i], parts[n].x[i], parts[n].y[i]);
			v_n = v(t[i], parts[n].x[i], parts[n].y[i]);

			// Apply Euler for first step
			if (i == 1){
				parts[n].x[i + 1] = parts[n].x[i] + dt * u_n;
				parts[n].y[i + 1] = parts[n].y[i] + dt * v_n;
			}

			// Apply Adams-Bashforth
			else{
				parts[n].x[i + 1] = parts[n].x[i] + dt * ((3. / 2.) * u_n - (1. / 2.) * u_nm1);
				parts[n].y[i + 1] = parts[n].y[i] + dt * ((3. / 2.) * v_n - (1. / 2.) * v_nm1);
			}

			// Write current velocities (n) to old variables (n-1)
			u_nm1 = u_n;
			v_nm1 = v_n;
		}
	}
}

// Gets step size
double Dsys::GetDt(){
    return dt;
}

// Prints trajectory data for given particle
void Dsys::PrintTraj(int n){
	// Print column headers
	printf("%6c%6c%6c\n", 't', 'x', 'y');

	// Iterate through position vectors
	for (std::size_t i = 0; i != t.size(); ++i){
		printf("%6.2f%6.2f%6.2f\n", t[i], parts[n].x[i], parts[n].y[i]);
	}
}

// Exports data to given file
void Dsys::ExportData(std::string filename){
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