#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H
#include <macros.h>
#include <fstream>

class Register_F : public sc_module {

  private:
  
    sc_uint<Dat_size> registers[Instruction_size];
  
  public:
  
    sc_in<bool> clock;
    sc_in< sc_uint<R_size> > op, r1, r2, r3;
    
    sc_in<bool> enable_wb;
    sc_in< sc_uint<R_size> > dir_Wback;
	  sc_in< sc_uint<Dat_size> > dat_Wback;
    
    sc_out< sc_uint<R_size> > op_out, r1_out;
    sc_out< sc_uint<Dat_size> > r3_out, r2_out;
    
    SC_CTOR(Register_F)
  {

    SC_METHOD(read);
      sensitive << clock.pos() << r1 << r2 << r3 ;
      
    SC_METHOD(write);
			sensitive << clock.neg() << dir_Wback;

    for(int i = 0; i < Instruction_size; ++i)
      registers[i] = i;

  }
  ~Register_F(){

    ofstream out("final_register.txt");
    
    for(int i = 0; i < Instruction_size; ++i)
      out << registers[i].to_int() << endl;
  }

    void read()
    {
    	op_out.write( op.read());
      r3_out.write( registers[ r3.read() ] );
      
      r1_out.write( r1.read() );
      
      if(op.read() == 2)
      	r2_out.write(registers[ r1.read()]);
      else
        r2_out.write( registers[ r2.read() ] );
    }
    
    void write() 
	{
		if (enable_wb)
		{
			registers[dir_Wback.read()] = dat_Wback.read();
		}
	}

};
#endif // REGISTER_FILE_H
