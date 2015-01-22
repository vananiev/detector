#ifndef _NOISE_GENERATOR
#define _NOISE_GENERATOR

#include <boost/random/normal_distribution.hpp>
#include <boost/random/lagged_fibonacci.hpp>
#include <boost/random/variate_generator.hpp>
#include <ctime>
#include "core.h"

using namespace std;

/* generate normal distributed noise */ 
class noise_generator
{
	private:
	boost::lagged_fibonacci19937 rnd_engine;
	boost::normal_distribution<double> distribution;

	public:
	noise_generator (const double mean, const double sigma);
	~noise_generator();
  	void generate_to (samples & noise);
	void set_sigma(const double & sigma);
	double sigma() const;
};

#endif
