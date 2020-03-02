#ifndef THIRD_PIPE_H
#define THIRD_PIPE_H

#include <systemc.h>
#include <iostream>
#include <macros.h>


class Pipe3 : public sc_module
{

  private:

		sc_uint <R_size> dir, op;
		sc_uint <Dat_size> data;
    sc_uint <Dir_mem_size>  dir_mem_aux;
		sc_signal<bool> enable;
		
  public:

    sc_in <bool> clock;

    sc_in < sc_uint<Dat_size> > data_in;
		sc_in < sc_uint<R_size> > dir_in, op_in;
		sc_in <bool> enable_in;
    sc_in < sc_uint<Dir_mem_size> > dir_mem_in;
   
		sc_out < sc_uint<Dat_size> > data_out;
		sc_out < sc_uint<R_size> > dir_out, op_out;
		sc_out<bool> enable_out;
    sc_out < sc_uint<Dir_mem_size> > dir_mem;

    SC_CTOR(Pipe3)
    {
      
      SC_METHOD(write);
        	sensitive << clock.neg() << dir_in ;

      SC_METHOD(read);
        sensitive << clock.pos() << data_in;
    }

    void write()
    {   
			dir = dir_in.read();
      data = data_in.read();
      op = op_in.read();
      dir_mem_aux = dir_mem_in.read();
			enable.write(enable_in);     
    }

    void read()
    {
    	dir_out.write(dir);
      data_out.write(data);
      op_out.write(op);
      dir_mem.write(dir_mem_aux);
      enable_out.write(enable);
    }

};

#endif //THIRD_PIPE_H
