#ifndef PIPE_H
#define PIPE_H

# include <systemc.h>
# include <iostream>
#include <vector>
#include <macros.h>

struct Register{

	sc_uint <R_size> operation;
	sc_uint <R_size> variable[3];
	sc_uint <Dir_mem_size> dir_aux;
};

class Pipe : public sc_module
{
	private:
		vector<Register> pipe;
		Register r;
  
	public:
		sc_in <bool> clock;
		sc_in <bool> enable;
		sc_in < sc_uint<Instruction_size> > instruction;

		sc_out < sc_uint<R_size> > op, r1, r2, r3;
		sc_out < sc_uint<Dir_mem_size> > dir_mem;

	void write()
	{   
		if(enable)
		{
			r.operation = instruction.read().range(15, 12);
			
			for(int i = 0, j = 11; i < 3; i++, j -= 4)
				r.variable[i] = instruction.read().range(j, j - 3); 

			r.dir_aux = instruction.read().range(Dir_mem_size,0);

			pipe.push_back(r);      
		}
	}

	void read()
	{
		op.write(r.operation);
		r1.write(r.variable[0]);
		r2.write(r.variable[1]);
		r3.write(r.variable[2]);
		dir_mem.write(r.dir_aux);
	}
  
	SC_CTOR(Pipe)
	{
		for(int i = 0 ; i < 3; i++)
			r.variable[i] = 0;

		r.operation = 0;
		r.dir_aux = 0;

		SC_METHOD(write);
			sensitive << clock.neg() << instruction;

		SC_METHOD(read);
			sensitive << clock.pos();
	}

	~Pipe() {
		pipe.clear();
	}
};

#endif //PIPE_H
