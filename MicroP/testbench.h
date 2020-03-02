#ifndef TESTBENCH_H
#define TESTBENCH_H

#include<macros.h>

SC_MODULE(testbench){

 	sc_in <bool> clock;

	sc_in < sc_uint<Dat_size> > data;

	void print()
	{
		cout << "  \t ";
		for (int i = 0; i < Dat_size; ++i)
		cout << data.read().range(Dat_size-(i+1),Dat_size-(i+1));
		
		cout << "  "<< sc_time_stamp() << endl;
		//cout << "    | " << clock.read() << endl;
	}
	
	void test()
	{
		cout << "\t        Data         | Clock " <<endl;
		cout << "\t-----------------------------" <<endl;
		
		for (int i = 0; i < 25; ++i){
			wait();
			print();
		}

		sc_stop();
	}
	
	SC_CTOR(testbench) {
		SC_THREAD(test);
			sensitive<<clock.pos();
	}
};

#endif //TESTBENCH_H
