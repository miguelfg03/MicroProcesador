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
	int IM_size;
	int inst_aux = 0;
	int count = 0;

	string aux; 

	sc_uint<Instruction_size> temp;

	void fetch() 
	{

		if(IM.good())
		{
			int position = PC*17*sizeof(char);
				
			if (position < IM_size)
			{
				IM.seekg(position);             
	 			string line;
				getline(IM,line);

				aux = line.substr(0, 4);

				for (int i = 0; i < Instruction_size; ++i)
					temp[i] = line[Instruction_size-(i+1)]-'0';

				instruction = temp;
				
				enable.write(true);

				if (aux == "0001")
				{
					instruction = temp;
					count = PC;
					PC++;
				}
				else
				{
					if ((count - PC > 1) or (PC - count > 1))
					{
						instruction = temp;
						PC++;
					}
					else
					{
						instruction.write(0);
						count++;
					}
				}

			}else
			{
				if(inst_aux <= 3)
				{
					instruction.write(0);
					enable.write(true);
					inst_aux++;
				}
				else
				{
					sc_stop();
				}
			}
		}
		else
		{
			sc_stop();
		}
	}

	SC_CTOR (Fetch) 
	{
		IM.open(Inst_mem, ios::in);
		IM.seekg(0,IM.end);
    	IM_size = IM.tellg();           
    	IM.seekg(0,IM.beg);

		PC = 0;

		SC_METHOD(fetch);
			sensitive << clk.neg();
	}

	~Fetch() {
		IM.close();
	}

};
#endif // FETCH_H