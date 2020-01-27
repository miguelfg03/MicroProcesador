#include <systemc.h>
#include <string>
#include "Fetch.h"
#include "Pipe.h"
#include "testbench.h"
#include "registre_file.h"
#include "Pipe2.h"

int sc_main(int argv, char* argc[]) {
  sc_time PERIOD(10,SC_NS);
  sc_time DELAY(10,SC_NS);
  sc_clock clock("clock",PERIOD,0.5,DELAY,true);

  Fetch ft("fetch");
  Pipe pi("pipe");
  Registre_F reg("Registre_file");
  Pipe2 pi2("pipe2");
  testbench tb("tb");

  sc_signal< sc_uint<Instruction_size> > instruction_sg;
  sc_signal< sc_uint<R_size> > op_sg1,r1_sg1,r2_sg1,r3_sg1, op_sg2, op_sgR, dir_w_back_sg;
  sc_signal<bool> connection_sg, connection_wb;
  sc_signal< sc_uint<Dat_size> > r1_sgR, r2_sgR, r3_sgR;
  sc_signal< sc_uint<Dat_size> > r1_sg2, r2_sg2, r3_sg2, r_w_back_sg;
	  
	ft.instruction(instruction_sg);
  ft.clk(clock);
	ft.connect(connection_sg);

	pi.clock(clock);
	pi.enable(connection_sg);
	pi.instruction(instruction_sg);
	pi.op(op_sg1);
	pi.r1(r1_sg1);
	pi.r2(r2_sg1);
	pi.r3(r3_sg1);
	
	reg.clock(clock);
	reg.enable(connection_sg);
	reg.enable_wb(connection_wb);
	reg.dir_w_back(dir_w_back_sg);
	reg.r_w_back(r_w_back_sg);
	reg.op(op_sg1);
	reg.r1(r1_sg1);
	reg.r2(r2_sg1);
	reg.r3(r3_sg1);
	
	reg.op_out(op_sgR);
	reg.r1_out(r1_sgR);
	reg.r2_out(r2_sgR);
	reg.r3_out(r3_sgR);
	
	pi2.clock(clock);
	pi2.enable(connection_sg);
	pi2.enable_wb(connection_wb);
	pi2.op(op_sg1);
	pi2.r1_in(r1_sgR);
	pi2.r2_in(r2_sgR);
	pi2.r3_in(r3_sgR);
	
	pi2.op_out(op_sg2);
	pi2.r1_out(r1_sg2);
	pi2.r2_out(r2_sg2);
	pi2.r3_out(r3_sg2);
	pi2.dir_w_back(dir_w_back_sg);
	pi2.r_w_back(r_w_back_sg);
	
 	tb.op(op_sg2);
	tb.r1(r1_sg2);
	tb.r2(r2_sg2);
	tb.r3(r3_sg2);
	tb.clock(clock);
	tb.enable(connection_sg);
	tb.enable_wb(connection_wb);
		
  sc_start();
  return 0;
}
