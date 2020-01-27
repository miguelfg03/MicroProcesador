#ifndef REGISTRE_FILE_H
#define REGISTRE_FILE_H
#include<macros.h>

class Registre_F : public sc_module {

  private:
  
    sc_uint<Dat_size> registers[Instruction_size];
  
  public:
  
    sc_in<bool> clock;
    sc_in<bool> enable;
    sc_in<bool> enable_wb;
    sc_in< sc_uint<R_size> > op, r1, r2, r3;
    
    sc_in< sc_uint<R_size> > dir_w_back;
	  sc_in< sc_uint<Dat_size> > r_w_back;
    
    sc_out< sc_uint<R_size> > op_out;
    sc_out< sc_uint<Dat_size> > r1_out, r2_out, r3_out;
    
    SC_CTOR(Registre_F)
  {

    SC_METHOD(read);
      sensitive << clock.neg() << r1 << r2 << r3;
      
    SC_METHOD(write);
			sensitive << clock.pos() << enable << enable_wb;

    for(int i = 0; i < Instruction_size; ++i)
      registers[i] = i;

  }

    void read()
    {
      r1_out.write( registers[ r1.read() ] );
      r2_out.write( registers[ r2.read() ] );
      r3_out.write( registers[ r3.read() ] );
    }
    
    void write() 
	{
		if (enable and enable_wb)
		{
			registers[dir_w_back.read()] = r_w_back.read();

      registers[0] = 0;
		}
	}

};
#endif
