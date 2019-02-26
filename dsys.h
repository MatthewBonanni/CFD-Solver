#include <vector>
#include <string>

typedef std::vector<double> dbvec;

class dsys {
        double dt;
		dbvec t, x, y;
	public:
        dsys(double, double, double);
        void fill_tvec(double);
        void march_ie();
		void march_ab();
        double getdt();
        void printtraj();
        void export_data(std::string);
};