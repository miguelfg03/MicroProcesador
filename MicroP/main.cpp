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

	sc_signal< sc_uint<Dat_size> > data_sg;
	 
	mp.clock(clock);
	mp.data(data_sg);
	
	tb.clock(clock);
	tb.data(data_sg);
		
  sc_start();
  return 0;
}
