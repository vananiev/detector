#include <noise_generator.h>

using namespace std;

noise_generator::
noise_generator (const double mean, const double sigma)
    			: distribution(mean,sigma), rnd_generator(rnd_engine, distribution){
	rnd_engine.seed(static_cast<unsigned>(std::time(0)));
}

noise_generator::
~noise_generator() { }

double
noise_generator::
operator() (){
	return rnd_generator();
}

void
noise_generator::
generate (vector<double> & noise){
	for(int i=0, cnt=noise.size(); i<cnt; i++){
		noise.at(i) = rnd_generator();
	}
}

