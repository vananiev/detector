#include <core.h>
#include <iostream>

using namespace std;

samples::
samples(const double & _sample_time):
	sample_time (_sample_time){}

samples::
samples():
	sample_time(0){}

void
samples::
set_sample_time(const double & v){
	sample_time = v;
}

samples::
samples(const double & _sample_time, int window_size){
    sample_time = _sample_time;
	sample.resize(window_size);
}

double
samples::
get_sample_time() const{
	return sample_time;
}

double
samples::
mean() const{
	double sum = 0;
	int cnt=sample.size();
    for(int i=0; i<cnt; i++){
        sum += sample[i];
    }
    return sum/cnt;
}

double
samples::
raw_moment(const int level) const{
	double sum = 0;
	int cnt=sample.size();
	for(int i=0; i<cnt; i++){
		sum += pow(sample[i],level);
	}
	return sum/cnt;
}

double
samples::
_deviation() const{
	double sum = 0;
	int cnt=sample.size();
    for(int i=0; i<cnt; i++){
        sum += sample[i]*sample[i];
    }
	return sum/cnt - pow(mean(),2);
}

double
samples::
deviation() const{
	int cnt=sample.size();
    return _deviation()*cnt/(cnt-1);
}

unsigned int
samples::
get_sample_count() const{
	return sample.size();
}

double
samples::
_central_moment4() const{
	double sum = 0;
	double m = mean();
    int cnt=sample.size();
    for(int i=0; i<cnt; i++){
        sum += pow (sample[i]-m, 4);
    }
	return sum/cnt;
}

double
samples::
excess() const{
	int n = sample.size();	
	double a = (pow(n,2)-1)/(n-2)/(n-3);
	double b = _central_moment4()/pow(_deviation(),2) + ((double)6)/(n+1) - 3.0;
	return a*b;
}

double
samples::
energy() const{
	if( !sample_time ){
		cout << "Can't calculate energy. Sample time is not set.";
		return 0;
	}
	double sum = 0;
    int cnt=sample.size();
    for(int i=0; i<cnt; i++){
        sum += pow (sample[i], 2);
    }
    return sum*sample_time;
}

void
samples::
set(const vector<double> & data_samples){
	sample = data_samples;
}

void
samples::
add(double s){
	sample.push_back(s);
}

void
samples::
set_window_size(int n){
	sample.resize(n);
}

samples&
samples::
operator=(const samples & right){
	sample_time = right.sample_time;
	sample = right.sample;
	return *this;	
}

samples
samples::
operator+(const samples & second) const{
	int f = sample.size();
    int s = second.sample.size();
	if(f>s){
		samples result = *this;
		for(int i=0; i<s; i++)
			result.sample[i] += second.sample[i];
		return result;
		}
	else{
		samples result = second;
		for(int i=0; i<f; i++)
            result.sample[i] += sample[i];
		return result;
	}
}

void
samples::
print() const{
	double max = -1e6, min = 1e6;
	for(int i=0, cnt=sample.size(); i<cnt; i++){
		double v = sample.at(i);
		if(v>max) max = v;
		if(v<min) min = v;
	}
	cout << "Samples: " << sample.size() << endl;
    cout << "Mean: " << mean() << endl;
	cout << "Max: " << max << endl;
	cout << "Min: " << min << endl;
    cout << "Deviation: " << deviation() << endl;
    cout << "Excess: " << excess() << endl;
    cout << "Energy: " << energy() << endl;
}

double
cross_correlation_0(samples X, samples Y){
	double sample_time = X.get_sample_time();
	if( sample_time == 0 || Y.get_sample_time() != sample_time ){
        cout << "Can't calculate cross_correlation(0) . Sample time is not set or X, Y sample times different.";
        return 0;
    }
	double sum = 0;
	int n = X.sample.size();
	int m = Y.sample.size();
    int cnt = (n<m)?n:m;
    for(int i=0; i<cnt; i++){
        sum += X.sample[i]*Y.sample[i];
    }
    return sum*sample_time;
}

double
treshold(double F, double sigma){
	return sqrt(2) * sigma * boost::math::erf_inv(1-2*F);
}
