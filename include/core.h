#ifndef _CORE
#define _CORE

#define CYCLES 1000

#include <math.h>
#include <vector>
#include <boost/math/special_functions/erf.hpp>

using namespace std;

class samples{
	private:
	double _deviation() const;
	double _central_moment4() const;
	double sample_time;

	public:
	vector<double> sample;
	double mean() const;
	double deviation() const;
	double raw_moment(const int level) const;
	double excess() const;
	double energy() const;
	samples(const double & sample_time);
	samples(const double & sample_time, int window_size);
	samples();
	void set_sample_time(const double & v);
	double get_sample_time() const;
	void print() const;
	void set(const vector<double> & data_samples);
	void add(double discret_sample);
	void set_window_size(int n);
	samples& operator=(const samples&);
	samples operator+(const samples&) const;
	unsigned int get_sample_count() const;
};

double cross_correlation_0(samples X, samples Y);
double treshold(double F, double sigma);

class kurtosis_detector{
	
};

class variables{
	private:
	double _sample_time;
	double _window_size;
	double _e0, _E0, _noise_sigma;
	samples _signal;
	
	public:
	variables() {_sample_time = 0; _window_size = 0; _e0 = 0; _E0 = 0; _noise_sigma=0; }
	void set_sample_time(const double & v) {_sample_time = v;}
	void set_window_size(const double & v) {_window_size = v;}
	void set_signal(samples & s) {_signal = s;}
	double sample_time() const {return _sample_time;}
	double window_size() const {return _window_size;}
	samples & signal() {return _signal;}
	void set_e0(const double & v) {_e0 = v;}
	void set_E0(const double & v) {_E0 = v;}
	double e0() const {return _e0;}
	double E0() const {return _E0;}
	void set_expected_noise_sigma(const double & v) { _noise_sigma = v;}
	double expected_noise_sigma() {return _noise_sigma;}
};

#endif
