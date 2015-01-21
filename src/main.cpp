#include <fstream>
#include <iostream>
#include <noise_generator.h>
#include <get_args.h>
#include <core.h>
#include "detection_table.h"

using namespace std;

void init(int argc, char * argv[]);
void calculate_tresholds(const double & noise_sigma);

variables info;

int main(int argc, char * argv[])
{
	init(argc, argv);

	cout << "Signal parameters... " <<  endl;
	info.signal().print();
	cout << endl;

	cout << "Expect-noise deviation, Volt: " << info.expected_noise_sigma() << endl;
	cout << "Window size in samples: " << info.window_size() << endl;
	cout << endl;

	calculate_tresholds (info.expected_noise_sigma());
	cout << "Excess treshold e0, o.e.: " << info.e0() << endl;
	cout << "Energy treshold E0, Joule: " << info.E0() << endl;
	cout << endl;	

	cout << "Calculate table..." << endl;
	vector<double> q;
	q.resize(200);
	for(int i=0, cnt=q.size(); i<cnt; i++)
		q[i] = 0.01 * (i+1);
	detection_table table( q, info.signal());
	table.calculate(info);
	table.print();
}

void init(int argc, char * argv[]){
	if(argc < 4){
        cout << "usage: " << argv[0] << " sample_time data_window_in_samples expect_noise_deviation /path/to/signal_filename" << endl;
        exit(1);
    }

    info.set_sample_time (atof (argv[1]));
    info.set_window_size (atoi (argv[2]));
	info.set_expected_noise_sigma (atoi (argv[3]));
	samples _signal = get_signal (argv[4]);
	_signal.set_sample_time (info.sample_time());
    info.set_signal (_signal);
}

void calculate_tresholds(const double & noise_sigma){
	const double mean = 0;
    noise_generator noiser(mean,noise_sigma);
    samples noise(info.sample_time());
    noise.set_window_size (info.window_size());

    samples e;
    samples z;

    for(int i=0; i<CYCLES; i++){
        noiser.generate_to (noise);
        e.add( noise.excess() );
        z.add( cross_correlation_0(noise, info.signal()) );
    }

    double sigma_e = e.deviation();
    double sigma_z = z.deviation();
    double F = 1 * info.window_size() * info.sample_time() / (24*3600*365);

	cout << "Deviation of expected-noise excess, o.e.: " << sigma_e << endl;
	cout << "Deviation of expected_noise-to-signal cross corelation (t=0), Joule: " << sigma_z << endl;
	cout << "Probability of false work in one sampling window, o.e.: " << F << endl;

	info.set_e0 ( treshold(F, sigma_e) );
    info.set_E0 ( treshold(F, sigma_z) );
}

