#include <fstream>
#include <string>
#include <macros.h>

#ifndef MEMORY_ACCESS_H
#define MEMORY_ACCESS_H

#define Mem_Access "data.txt"

using namespace std;

SC_MODULE (Mem_A){

	fstream MA;
	sc_in<bool> clk;
	
	sc_in<bool> enable;
	sc_in < sc_uint<R_size> > op;
	sc_in < sc_uint<Dir_mem_size> > dir_in; 
 	sc_in < sc_uint<Dat_size> > data_in;

	sc_out < sc_uint<Dat_size> > data_out;
	sc_out<bool> enable_out;
	
	sc_uint <Dat_size> data_aux;
	sc_uint <R_size> dir_aux;
	sc_uint <Dat_size> temp;
	
	bool enable_aux = false;

	int position, pos;

	void read() 
	{
		if(op.read()==1){
			if(MA.good())
			{
				position = dir_in.read()*17*sizeof(char);
                
				MA.seekg(position);             
      			string line;
				getline(MA,line);

				for (int i = 0; i < Dat_size; ++i)
					temp[i] = line[Dat_size-(i+1)]-'0';

				data_out.write(temp);
				enable_aux = true;
			}
		
		}else{	
			data_out.write(data_in.read());
		}
	}

	void write()
	{
		if(enable and op.read()==2)
		{
			if(MA.good()){
				pos = dir_in.read()*17*sizeof(char);

				MA.seekp(pos, ios::beg); 
				for (int i = 0; i < Dat_size; ++i)
				MA << data_in.read().range(Dat_size-(i+1),Dat_size-(i+1)); 
				//MA << data_in;

				enable_out.write(false);
			}
			else 
			{
				sc_stop();
			}
		}else {
			enable_out.write(true);
		}
	}

	SC_CTOR (Mem_A) 
	{
		MA.open(Mem_Access, ios::in | ios::out);

		position = 0;
		pos = 0;

		SC_METHOD(read);
			sensitive << clk.neg() << dir_in;

		SC_METHOD(write);
			sensitive << clk.pos() << enable << data_in << op;
	}

	~Mem_A() {
		MA.close();
	}

};
#endif // MEMORY_ACCESS_H