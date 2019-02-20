#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>

typedef std::vector<double> dbvec;

// Define trajectory data structure
struct tpos {
	dbvec t;
	dbvec x;
	dbvec y;
} traj;

// Function definitions
dbvec tvec(double t0, double dt, double tmax);
void write_out(tpos &traj);

// x velocity function
double u(double t, double x, double y){
    return x - y + 1;
}

// y velocity function
double v(double t, double x, double y){
	return 2*x - y;
}

int main(){

	// Time parameters
	float dt = 0.1;
	float tmax = 10;

	// Initial conditions
	double x0 = 1.5;
	double y0 = 2;

	// Create trajectory vector
	traj.t = tvec(0, dt, tmax);

	// Compute number of time steps
	int N = traj.t.size();

	// Allocate memory for position vectors
	traj.x.resize(N+1);
	traj.y.resize(N+1);

	// Initialize tpos
	traj.x[0] = x0;
	traj.y[0] = y0;

	// Initialize neighbor variables
	double u_n = 0, v_n = 0;
	double u_nm1 = 0, v_nm1 = 0;

	// Time marching
	for (std::size_t i = 0; i != traj.t.size(); ++i){

		// Compute velocity components
		u_n = u(traj.t[i], traj.x[i], traj.y[i]);
		v_n = v(traj.t[i], traj.x[i], traj.y[i]);

		// Apply Euler for first step
		if (i == 1){
			traj.x[i+1] = traj.x[i] + dt * u_n;
			traj.y[i+1] = traj.y[i] + dt * v_n;
		}

		// Apply Adams-Bashforth
		else {
			traj.x[i+1] = traj.x[i] + dt * ((3./2.) * u_n - (1./2.) * u_nm1);
			traj.y[i+1] = traj.y[i] + dt * ((3./2.) * v_n - (1./2.) * v_nm1);
		}

		// Write current velocities (n) to old variables (n-1)
		u_nm1 = u_n;
		v_nm1 = v_n;
	}

	// Export trajectory to csv
	write_out(traj);

	return 0;
}

// Generates equally-spaced time vector
dbvec tvec(double t0, double dt, double tmax){

	// Compute number of required steps
	float len = ((tmax - t0) / dt) + 1;
	
	// Create empty time vector
	dbvec t(len);

	// Iterate through time vector
	for (auto it = t.begin(); it != t.end(); ++it){
		auto i = std::distance(t.begin(), it);

		*it = dt * i;
	}

	return t;
}

// Exports trajectory data to csv
void write_out(tpos &traj){
	std::ofstream outfile;
	outfile.open("dynsys_data.csv");

	// Write headers
	outfile << "t,x,y\n";

	// Iterate through trajectory data, write each line
	for (std::size_t i = 0; i != traj.t.size(); ++i){
		outfile << std::to_string(traj.t[i]) << ","
				<< std::to_string(traj.x[i]) << ","
				<< std::to_string(traj.y[i]) << "\n";
	}

	outfile.close();
}
