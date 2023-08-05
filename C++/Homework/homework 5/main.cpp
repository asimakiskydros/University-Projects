#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
	char filename[50];
	char k,read;
	int count=0;
	ifstream ifs;
	cin>>k>>filename;
	ifs.open(filename);
	if(ifs.is_open()){
		while(ifs>>read)
			if(read==k)
				count++;
		cout<<count;
	}
	else
		cout<<"File error";	
}