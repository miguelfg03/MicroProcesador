#include <fstream>
#include <string>
#include <macros.h>

#ifndef FETCH_H
#define FETCH_H

#define Inst_mem "inst.txt"

using namespace std;

SC_MODULE (Fetch){

	ifstream IM;
	sc_in<bool> clk;
	sc_out<bool> enable;
	sc_out< sc_uint<Instruction_size> > instruction;

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
 			sc_uint<Instruction_size> temp;

			for (int i = 0; i < Instruction_size; ++i)
				temp[i] = line[Instruction_size-(i+1)]-'0';

			instruction = temp;
			enable.write(true);
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
			sensitive<<clk.neg();
	}

	~Fetch() {
		IM.close();
	}

};
#endif // FETCH_H
