#ifndef TESTBENCH_H
#define TESTBENCH_H

SC_MODULE(testbench){

	sc_in <bool> clock;
	sc_out <bool> enable;
	sc_out <bool> enable_wb;
  
  sc_in < sc_uint<R_size> > op;
  sc_in < sc_uint<Dat_size> > r1, r2, r3;

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
		cout << r3.read().range(Dat_size-(i+1),Dat_size-(i+1));
		cout << "    | " << clock.read() << endl;
	}
	
	void test()
	{
		cout << "\t Operador | Registro1 | Registro2 | Registro3 | Clock " <<endl;
		cout << "\t-----------------------------------------------------" <<endl;
		
		for (int i = 0; i < 9; ++i){
		  enable.write(true);
		  enable_wb.write(false);
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
