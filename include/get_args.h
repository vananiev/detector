#include <fstream>
#include <iostream>

using namespace std;

vector<double> get_signal(char * filename){
	vector<double> signal;
	
	ifstream in(filename);
    if(!in){
        cout << "File " << filename << " not found" << endl;
        return signal;
    }
    double s;
	while(in >> s){
		signal.push_back(s);
	}
	in.close();
	return signal;
}
