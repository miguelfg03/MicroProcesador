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
    sc_in <bool> enable, enable_wb;
    sc_in < sc_uint<R_size> > op;
    sc_in < sc_uint<Dat_size> > r3_in, r2_in, r1_in;
   
    
    sc_out < sc_uint<R_size> > dir_w_back;
	  sc_out < sc_uint<Dat_size> > r_w_back;
    sc_out < sc_uint<R_size> > op_out; 
    sc_out < sc_uint<Dat_size> > r3_out, r2_out, r1_out;

    SC_CTOR(Pipe2)
    {
      for(int i = 0 ; i < 3; i++)
        r.variable[i] = 0;

      r.operation = 0;
      
      SC_METHOD(write);
        sensitive << clock.pos() << enable << op << r3_in << r2_in << r1_in;

      SC_METHOD(read);
        sensitive << clock.neg();
    }

    void write()
    {   
      if(enable)
        {
          r.operation = op.read();
          r.variable[0] = r1_in.read();
          r.variable[1] = r2_in.read();
          r.variable[2] = r3_in.read();
          pipe.push_back(r); 
        }
       
      if(enable_wb)
       {
          dir_w_back.write(op.read());
          r_w_back.write(r1_in.read());
       }
       
    }

    void read()
    {
      op_out.write(r.operation);
      r1_out.write(r.variable[0]);
      r2_out.write(r.variable[1]);
      r3_out.write(r.variable[2]);
      
    }

};



#endif
