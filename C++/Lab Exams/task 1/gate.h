#ifndef gate_h
#define gate_h
#include <string>
using namespace std;

class gate{
	protected:
		string label;
	public:
		gate();
		gate(string);
		void setLabel(string);
		string getLabel();
		virtual int getOutput();
		virtual int getPins();
		virtual void setPin(int,int);
		virtual int getPin(int);
};

#endif //gate_h