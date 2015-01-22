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

	for(int i=0, cnt=q.size(); i<cnt; i++){
		{
            cout << "\r" <<  (int)100.0*i/cnt << "%" << "  ";
			cout.flush();
        }
		double noise_sigma = sqrt( signal.energy() / q.at(i) / signal.duration() );
		noiser.set_sigma (noise_sigma);
		calc_table_row(noiser, info);
	}
	cout << "\r     \r";
}

void
detection_table::
calc_table_row( noise_generator & noiser, const variables & info){
	static samples noise(info.sample_time(), info.window_size());

	int cnt_e = 0, cnt_z = 0;
	for(int i=0; i<CYCLES; i++){
		noiser.generate_to (noise);
		samples signal_with_noise = signal + noise;
		if( signal_with_noise.excess() >= info.e0() ) cnt_e++;
		if( cross_correlation_0(signal_with_noise, info.signal()) >= info.z0() ) cnt_z++;
	}
	Pe.push_back ( ((double)cnt_e) / CYCLES );
	Pz.push_back ( ((double)cnt_z) / CYCLES );
}

void
detection_table::
print() const{
	cout << "q\tP_e\tP_z" << endl;
	cout << "----------------------"  << endl;
	for(int i=0, cnt=q.size(); i<cnt; i++){
		cout << q.at(i) << "\t" << Pe.at(i) << "\t" << Pz.at(i) << endl;
	}
}

