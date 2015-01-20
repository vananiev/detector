#include <math.h>
#include <vector>

using namespace std;

class samples{
	private:
	double _deviation();
	double _central_moment4();
	const double sample_time;

	public:
	vector<double> sample;
	double mean();
	double deviation ();
	double raw_moment(const int level);
	double excess();
	double energy();
	samples(double sample_time);
	samples();
	const double get_sample_time();
	void print();
	void set(const vector<double> & data_samples);
};

double cross_correlation_0(samples X, samples Y);

class kurtosis_detector{
	
};
