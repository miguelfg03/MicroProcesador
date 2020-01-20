#include <fstream>
#include <string>
#include <Pipe.h>

#ifndef FETCH_H
#define FETCH_H

#define Inst_mem "inst.txt"

using namespace std;


SC_MODULE (Fetch) {

	ifstream IM;
	Pipe* pi;
  sc_in<bool> clk;
	int PC;
  sc_signal<bool> connect;
	sc_out< sc_uint<16> > instruction;
	sc_out < sc_uint<4> > op, r1, r2, r3;


	void fetch() {
    char line[16];
		IM.seekg(PC*16, ios::beg);
		IM.read(line, 16 );
    PC = PC+1;
		sc_uint<16> temp;
		for (int i = 0; i < 16; ++i)
      temp[i] = line[16-(i+1)]-'0';
    instruction = temp;
    connect.write(true);

	}
  	

  SC_CTOR (Fetch) {
		IM.open(Inst_mem, ios::in);
		PC = 0;
		pi = new Pipe("pipe");
		pi->clock(clk);
		pi->enable(connect);
		pi->instruction(instruction);
		pi->op(op);
		pi->r1(r1);
		pi->r2(r2);
		pi->r3(r3);

    SC_METHOD(fetch);
   		sensitive<<clk.neg();
  }

  ~Fetch() {
    IM.close();
  }
};

#endif // FETCH_H
