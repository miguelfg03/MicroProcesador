#ifndef PIPELINE_H
#define PIPELINE_H

#define IM_length 16

# include <systemc.h>
# include <iostream>
# include <iomanip>

class Pipe : public sc_module
{

	private:
	
  sc_uint <4> operation;
  sc_uint <4> variable[3];

	public:

  sc_in <bool> clock;
  sc_in <bool> enable;
  sc_in < sc_uint<IM_length> > instruction;

  sc_out < sc_uint<4> > op, r1, r2, r3;

  void write()
  {   
    if(enable)
      {
      
	      operation = instruction.read().range(15, 12);

        for(int i = 0, j = 11; i < 3; i++, j -= 4)
          variable[i] = instruction.read().range(j, j - 3);

      }
  }

  void read()
  {
    op.write(operation);
    r1.write(variable[0]);
    r2.write(variable[1]);
    r3.write(variable[2]);

  }
  
  SC_CTOR(Pipe)
  {
    for(int i = 0 ; i < 3; i++)
      variable[i] = 0;

    operation = 0;

    SC_METHOD(write);
      sensitive << clock.neg() << enable << instruction;

    SC_METHOD(read);
      sensitive << clock.pos() << op;
  }
};

#endif
