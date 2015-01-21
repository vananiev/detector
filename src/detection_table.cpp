#include "detection_table.h"
#include "noise_generator.h"

using namespace std;

detection_table::
detection_table(vector<double> & _q, samples _signal):
	q(_q), signal(_signal)
{}

void
detection_table::
calculate(const variables & info){
	noise_generator noiser(0,1);
	double signal_energy = signal.energy();
	double T = signal.get_sample_time() * signal.get_sample_count();

	for(int i=0, cnt=q.size(); i<cnt; i++){
		double noise_sigma = sqrt( signal_energy / q.at(i) / T );
		//cout << "Noise deviation: " << noise_sigma << endl;
		noiser.set_sigma (noise_sigma);
		calc_table_row(noiser, info);
	}

}

void
detection_table::
calc_table_row( noise_generator & noiser, const variables & info){
	static samples noise(info.sample_time(), info.window_size());

noiser.generate_to (noise);
        samples signal_with_noise = signal + noise;
//signal_with_noise.print();

	int cnt_e = 0, cnt_E = 0;
	for(int i=0; i<CYCLES; i++){
		noiser.generate_to (noise);
		samples signal_with_noise = signal + noise;
		if( signal_with_noise.excess() >= info.e0() ) cnt_e++;
		if( signal_with_noise.energy() >= info.E0() ) cnt_E++;
	}
	Pe.push_back ( ((double)cnt_e) / CYCLES );
	PE.push_back ( ((double)cnt_E) / CYCLES );
}

void
detection_table::
print() const{
	cout << "q\tP_e\tP_E" << endl;
	cout << "----------------------"  << endl;
	for(int i=0, cnt=q.size(); i<cnt; i++){
		cout << q.at(i) << "\t" << Pe.at(i) << "\t" << PE.at(i) << endl;
	}
}

