#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>

typedef std::vector<double> dbvec;

struct tpos {
	dbvec t;
	dbvec x;
	dbvec y;
} traj;

dbvec tvec(double t0, double dt, double tmax);
void write_out(tpos &traj);

double u(double t, double x, double y){
    return x - y + 1;
}

double v(double t, double x, double y){
	return 2*x - y;
}

int main(){

	float dt = 0.1;
	float tmax = 10;

	double x0 = 1.5;
	double y0 = 2;

	traj.t = tvec(0, dt, tmax);

	int N = traj.t.size();

	traj.x.resize(N+1);
	traj.y.resize(N+1);

	traj.x[0] = x0;
	traj.y[0] = y0;

	double u_n = 0, v_n = 0;
	double u_nm1 = 0, v_nm1 = 0;

	for (std::size_t i = 0; i != traj.t.size(); ++i){

		u_n = u(traj.t[i], traj.x[i], traj.y[i]);
		v_n = v(traj.t[i], traj.x[i], traj.y[i]);

		if (i == 1){
			traj.x[i+1] = traj.x[i] + dt * u_n;
			traj.y[i+1] = traj.y[i] + dt * v_n;
		}
		else {
			traj.x[i+1] = traj.x[i] + dt * ((3./2.) * u_n - (1./2.) * u_nm1);
			traj.y[i+1] = traj.y[i] + dt * ((3./2.) * v_n - (1./2.) * v_nm1);
		}

		u_nm1 = u_n;
		v_nm1 = v_n;
	}

	write_out(traj);

	return 0;
}

dbvec tvec(double t0, double dt, double tmax){
	float len = ((tmax - t0) / dt) + 1;
	
	dbvec t(len);

	for (auto it = t.begin(); it != t.end(); ++it){
		auto i = std::distance(t.begin(), it);

		*it = dt * i;
	}

	return t;
}

void write_out(tpos &traj){
	std::ofstream outfile;
	outfile.open("dynsys_data.csv");

	outfile << "t,x,y\n";

	for (std::size_t i = 0; i != traj.t.size(); ++i){
		outfile << std::to_string(traj.t[i]) << ","
				<< std::to_string(traj.x[i]) << ","
				<< std::to_string(traj.y[i]) << "\n";
	}

	outfile.close();
}
