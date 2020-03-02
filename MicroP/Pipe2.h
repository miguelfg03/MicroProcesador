#ifndef SECOND_PIPE_H
#define SECOND_PIPE_H
#include<macros.h>

class Pipe2 : public sc_module
{

  private:

    vector<Register> pipe;
		Register r;
		
  public:

    sc_in <bool> clock;

    sc_in < sc_uint<R_size> > op_in, r1_in;
    sc_in < sc_uint<Dat_size> > r3_in, r2_in;
    sc_in < sc_uint<Dir_mem_size> > dir_mem_in;
   
    sc_out < sc_uint<R_size> > op_out, r1_out; 
    sc_out < sc_uint<Dat_size> > r2_out, r3_out;
    sc_out < sc_uint<Dir_mem_size> > dir_mem;

    sc_uint <Dir_mem_size> dir_mem_aux;
    sc_uint <Dat_size> variable[2];

    SC_CTOR(Pipe2)
    {
      for(int i = 0 ; i < 2; i++)
        	variable[i] = 0;

      r.operation = 0;
      
      SC_METHOD(write);
        	sensitive << clock.neg() << op_in << r3_in << r2_in << r1_in;

      SC_METHOD(read);
        sensitive << clock.pos();
    }

    void write()
    {   
			r.operation = op_in.read();
      variable[0] = r2_in.read();
      variable[1] = r3_in.read();
      
      dir_mem_aux = dir_mem_in.read();
      pipe.push_back(r); 
       
    }

    void read()
    {
    	op_out.write(r.operation);
      r2_out.write(variable[0]);
      r3_out.write(variable[1]);
      r1_out.write(r1_in.read());
      dir_mem.write(dir_mem_aux);
      
    }

};



#endif //SECOND_PIPE_H
