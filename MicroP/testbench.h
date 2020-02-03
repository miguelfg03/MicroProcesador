#ifndef TESTBENCH_H
#define TESTBENCH_H

#include<macros.h>

SC_MODULE(testbench){

 	sc_in <bool> clock;
	sc_out <bool> enable_wb;

	sc_out < sc_uint<R_size> > dir_Wback;
	sc_out < sc_uint<Dat_size> > dat_Wback;

	sc_in < sc_uint<R_size> > op;
	sc_in < sc_uint<Dat_size> > r1, r2, result;

	void print()
	{
		cout << "   ";
		for (int i = 0; i < R_size; ++i)
		cout << op.read().range(R_size-(i+1),R_size-(i+1));
		cout << "   |   ";
		
		for (int i = 0; i < Dat_size; ++i)
		cout << r1.read().range(Dat_size-(i+1),Dat_size-(i+1));
		cout << "    |   ";
		
		for (int i = 0; i < Dat_size; ++i)
		cout << r2.read().range(Dat_size-(i+1),Dat_size-(i+1));
		cout << "    |   ";
		
		for (int i = 0; i < Dat_size; ++i)
		cout << result.read().range(Dat_size-(i+1),Dat_size-(i+1));
		cout << "    | " << clock.read() << endl;
	}
	
	void test()
	{
		cout << "\t Operador | Registro1 | Registro2 | Registro3 | Clock " <<endl;
		cout << "\t-----------------------------------------------------" <<endl;
		
		for (int i = 0; i < 9; ++i){
		  enable_wb.write(false);
			dir_Wback.write(0);
			dat_Wback.write(0);
			wait();
			print();
		}

		for (int i = 0; i < 9; ++i){
		  enable_wb.write(true);
			dir_Wback.write(3);
			dat_Wback.write(10);
			wait();
			print();
		}
		
		sc_stop();
	}
	
	SC_CTOR(testbench) {
		SC_THREAD(test);
			sensitive<<clock.neg();
	}
};

#endif //TESTBENCH_H
