#ifndef FOUR_PIPE_H
#define FOUR_PIPE_H
#include<macros.h>

class Pipe4 : public sc_module
{

  private:

    sc_uint <R_size> dir;
		sc_uint <Dat_size> data;
    sc_signal<bool> enable;

  public:

    sc_in <bool> clock;

    sc_in < sc_uint<Dat_size> > data_in;
		sc_in < sc_uint<R_size> > dir_in;
		sc_in<bool> enable_in;
   
		sc_out < sc_uint<Dat_size> > data_out;
		sc_out < sc_uint<R_size> > dir_out;
		sc_out<bool> enable_out;

    SC_CTOR(Pipe4)
    {
			SC_METHOD(write);
        	sensitive << clock.neg() << dir_in;

      SC_METHOD(read);
        sensitive << clock.pos() << data_in << dir_in;
    }

    void write()
    {   
			dir = dir_in.read();
      data = data_in.read();
			enable.write(enable_in);
    }

    void read()
    {
    	dir_out.write(dir);
      data_out.write(data);
      enable_out.write(enable); 
    }

};

#endif //FOUR_PIPE_H
