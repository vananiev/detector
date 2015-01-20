#include <boost/random/normal_distribution.hpp>
#include <boost/random/lagged_fibonacci.hpp>
#include <boost/random/variate_generator.hpp>
#include <ctime>
#include <vector>

using namespace std;

/* generate normal distributed noise */ 
class noise_generator
{
	private:
	boost::lagged_fibonacci19937 rnd_engine;
	boost::normal_distribution<double> distribution;
	boost::variate_generator< boost::lagged_fibonacci19937 &, boost::normal_distribution<> >  rnd_generator;

	public:
	noise_generator (const double mean, const double sigma);
	~noise_generator();
  	void generate (vector<double> & noise);

	protected:
	double operator() ();
};
