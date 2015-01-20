#include <core.h>
#include <iostream>

using namespace std;

samples::
samples(double _sample_time):
	sample_time (_sample_time){}

samples::
samples():
	sample_time(0){}

const double
samples::
get_sample_time(){
	return sample_time;
}

double
samples::
mean(){
	double sum = 0;
	int cnt=sample.size();
    for(int i=0; i<cnt; i++){
        sum += sample[i];
    }
    return sum/cnt;
}

double
samples::
raw_moment(const int level){
	double sum = 0;
	int cnt=sample.size();
	for(int i=0; i<cnt; i++){
		sum += pow(sample[i],level);
	}
	return sum/cnt;
}

double
samples::
_deviation(){
	double sum = 0;
	int cnt=sample.size();
    for(int i=0; i<cnt; i++){
        sum += sample[i]*sample[i];
    }
	return sum/cnt - pow(mean(),2);
}

double
samples::
deviation(){
	int cnt=sample.size();
    return _deviation()*cnt/(cnt-1);
}

double
samples::
_central_moment4(){
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
excess(){
	int n = sample.size();	
	double a = (pow(n,2)-1)/(n-2)/(n-3);
	double b = _central_moment4()/pow(_deviation(),2) + ((double)6)/(n+1) - 3.0;
	return a*b;
}

double
samples::
energy(){
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
print(){
	cout << endl;
    cout << "Mean: " << mean() << endl;
    cout << "Deviation: " << deviation() << endl;
    cout << "Excess: " << excess() << endl;
    cout << "Energy: " << energy() << endl;
	cout << endl;
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
