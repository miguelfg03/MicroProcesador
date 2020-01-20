#ifndef TESTBENCH_H
#define TESTBENCH_H

SC_MODULE(testbench){

	sc_in <bool> clock;
  sc_in < sc_uint<16> > instruction;

  sc_in < sc_uint<4> > op, r1, r2, r3;

	void print(){
	
		cout << "\t  ";
		for (int i = 0; i < 4; ++i)
		cout << op.read().range(4-(i+1),4-(i+1));
		cout << "    |  ";
		
		for (int i = 0; i < 4; ++i)
		cout << r1.read().range(4-(i+1),4-(i+1));
		cout << "     |  ";
		
		for (int i = 0; i < 4; ++i)
		cout << r2.read().range(4-(i+1),4-(i+1));
		cout << "     |  ";
		
		for (int i = 0; i < 4; ++i)
		cout << r3.read().range(4-(i+1),4-(i+1));

		cout << "     |  " << clock.read() << endl;
		
	}
	
	void test(){
	
		cout << "\t Operador | Registro1 | Registro2 | Registro3 | Clock " <<endl;
		cout << "\t-----------------------------------------------------" <<endl;
		
		for (int i = 0; i < 7; ++i){
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

#endif
