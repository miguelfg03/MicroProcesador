#include <systemc.h>
#include <string>
#include "Fetch.h"
#include "Pipe.h"
#include "testbench.h"


int sc_main(int argv, char* argc[]) {
  sc_time PERIOD(10,SC_NS);
  sc_time DELAY(10,SC_NS);
  sc_clock clock("clock",PERIOD,0.5,DELAY,true);

  Fetch ft("fetch");
  testbench tb("tb");

  sc_signal< sc_uint<16> > instruction_sg, instruction_sg1;
  sc_signal< sc_uint<4> > op_sg,r1_sg,r2_sg,r3_sg;
  sc_signal<bool> connect_sg;

	ft.instruction(instruction_sg);
  ft.clk(clock);
	ft.op(op_sg);
	ft.r1(r1_sg);
	ft.r2(r2_sg);
	ft.r3(r3_sg);
	
 	tb.op(op_sg);
	tb.r1(r1_sg);
	tb.r2(r2_sg);
	tb.r3(r3_sg);
	tb.clock(clock);
	tb.instruction(instruction_sg);
	
  sc_start();
  return 0;
}
