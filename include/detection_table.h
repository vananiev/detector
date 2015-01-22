#ifndef _DETECTION_TABLE
#define _DETECTION_TABLE

#include "core.h"
#include "noise_generator.h"

using namespace std;

class detection_table{
	private:
	const vector<double> q; // signal/noise
	const samples signal;
	void calc_table_row(noise_generator & noiser, const variables & info);

    public:
    vector<double> Pe;
    vector<double> Pz;
	
	detection_table(vector<double> & q, samples signal);
    void calculate(const variables & info);
	void print() const;
};

#endif
