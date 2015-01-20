#include <fstream>
#include <iostream>
#include <noise_generator.h>
#include <get_args.h>
#include <core.h>

using namespace std;

int main(int argc, char * argv[])
{
	if(argc < 4){
		cout << "usage: " << argv[0] << " sample_time data_window_in_samples /path/to/signal_filename" << endl;
		return 1;
	}

	const double sample_time = atof (argv[1]);
	const unsigned int window = atoi (argv[2]);
	samples signal( sample_time );
	signal.set (get_signal (argv[3]));

	cout << "Sampling time: " << sample_time << endl;
	cout << "Signal samples: " << signal.sample.size() << endl;

	const double mean = 0;
    const double sigma = 1;
    noise_generator noiser(mean,sigma);
    samples noise(sample_time);
	noise.sample.resize(window);

	samples e;
	samples z;	

	int cycles = 1000;
	for(int i=0; i<cycles; i++){
		noiser.generate (noise.sample);
		e.sample.push_back( noise.excess() );
		z.sample.push_back( cross_correlation_0(noise, signal) );		
	}

	double sigma_e = e.deviation();
	double sigma_z = z.deviation();

	cout << sigma_e << endl << sigma_z << endl;	
}
