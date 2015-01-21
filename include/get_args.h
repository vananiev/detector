#include <fstream>
#include <iostream>
#include "core.h"

using namespace std;

samples get_signal(char * filename){
	samples signal;
	
	ifstream in(filename);
    if(!in){
        cout << "File " << filename << " not found" << endl;
        return signal;
    }
    double s;
	while(in >> s){
		signal.add(s);
	}
	in.close();
	return signal;
}
