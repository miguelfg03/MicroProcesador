#include <fstream>
#include <string>

#ifndef FETCH_H
#define FETCH_H

#define Inst_mem "inst.txt"
#define IM_length 16

using namespace std;

SC_MODULE (Fetch){

	ifstream IM;
	sc_in<bool> clk;
	sc_in<bool> connect;
	sc_out< sc_uint<IM_length> > instruction;

	int PC;


	void fetch() 
	{

		if(IM.good())
		{
			int position = PC*17*sizeof(char);
                
			IM.seekg(position);             
      string line;
			getline(IM,line);

			PC++;
 			sc_uint<IM_length> temp;

			for (int i = 0; i < IM_length; ++i)
				temp[i] = line[IM_length-(i+1)]-'0';

			instruction = temp;
		}
		else
		{
			sc_stop();
		}
	}

	SC_CTOR (Fetch) 
	{
		IM.open(Inst_mem, ios::in);

		PC = 0;

		SC_METHOD(fetch);
			sensitive<<clk.neg() ;
	}

	~Fetch() {
		IM.close();
	}

};
#endif // FETCH_H
