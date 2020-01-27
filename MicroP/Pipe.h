#ifndef PIPELINE_H
#define PIPELINE_H

# include <systemc.h>
# include <iostream>
#include <vector>
#include<macros.h>

struct Register{

	sc_uint <R_size> operation;
	sc_uint <R_size> variable[3];

};

class Pipe : public sc_module
{
	private:
		vector<Register> pipe;
		Register r;
  
	public:
		sc_in <bool> clock;
		sc_in <bool> enable;
		sc_in < sc_uint<IM_length> > instruction;

		sc_out < sc_uint<R_size> > op, r1, r2, r3;

	void write()
	{   
		if(enable)
		{
			r.operation = instruction.read().range(15, 12);
			
			for(int i = 0, j = 11; i < 3; i++, j -= 4)
				r.variable[i] = instruction.read().range(j, j - 3); 

			pipe.push_back(r);       
		}
	}

	void read()
	{
		op.write(r.operation);
		r1.write(r.variable[0]);
		r2.write(r.variable[1]);
		r3.write(r.variable[2]);
	}
  
	SC_CTOR(Pipe)
	{
		for(int i = 0 ; i < 3; i++)
			r.variable[i] = 0;

		r.operation = 0;

		SC_METHOD(write);
			sensitive << clock.neg() << enable << instruction;

		SC_METHOD(read);
			sensitive << clock.pos();
	}

	~Pipe() {
		pipe.clear();
	}
};

#endif //PIPELINE_H
