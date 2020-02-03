#include <systemc.h>
#include <string>
#include "microp.h"
#include "testbench.h"

int sc_main(int argv, char* argc[]) {
  sc_time PERIOD(10,SC_NS);
  sc_time DELAY(10,SC_NS);
  sc_clock clock("clock",PERIOD,0.5,DELAY,true);

  MicroP mp("microp");
  testbench tb("tb");

	sc_signal<bool> connection_wb;
  sc_signal< sc_uint<R_size> > dir_Wback_sg, op_sg;
  sc_signal< sc_uint<Dat_size> > dat_Wback_sg,r1_sg, r2_sg, result_sg;
	 
	mp.clock(clock);
	mp.enable_wb(connection_wb);
	mp.dir_Wback(dir_Wback_sg);
	mp.dat_Wback(dat_Wback_sg);
	mp.op(op_sg);
	mp.r1(r1_sg);
	mp.r2(r2_sg);
	mp.result(result_sg);
	
	tb.clock(clock);
	tb.enable_wb(connection_wb);
	tb.dir_Wback(dir_Wback_sg);
	tb.dat_Wback(dat_Wback_sg);
 	tb.op(op_sg);
	tb.r1(r1_sg);
	tb.r2(r2_sg);
	tb.result(result_sg);
		
  sc_start();
  return 0;
}
