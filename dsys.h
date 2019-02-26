#include <vector>
#include <string>
#include <functional>

typedef std::vector<double> dbvec;

class dsys {
        double dt;
		dbvec t, x, y;
        std::function<double(double, double, double)> u;
        std::function<double(double, double, double)> v;
	public:
        dsys(double, double, double);
        void fill_tvec(double);
        void set_vel(double (*u_in)(double, double, double),
                     double (*v_in)(double, double, double));
        void march_ie();
        void march_ab();
        double getdt();
        void printtraj();
        void export_data(std::string);
};