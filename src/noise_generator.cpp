#include <noise_generator.h>

using namespace std;

noise_generator::
noise_generator (const double mean, const double sigma)
    			: distribution(mean,sigma){
	rnd_engine.seed(static_cast<unsigned>(std::time(0)));
}

noise_generator::
~noise_generator() { }

void
noise_generator::
generate_to (samples & noise){
	for(int i=0, cnt=noise.sample.size(); i<cnt; i++){
		noise.sample[i] = distribution (rnd_engine);
	}
}

void
noise_generator::
set_sigma(const double & sigma){
	distribution =  boost::normal_distribution<double>(distribution.mean(), sigma);
}
