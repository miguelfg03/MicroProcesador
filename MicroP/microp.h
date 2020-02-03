#include <systemc.h>
#include <iostream>
#include <Fetch.h>
#include <Pipe.h>
#include <register_file.h>
#include <Pipe2.h>
#include <execute.h>
#include<macros.h>

#ifndef MICROPROCESADOR_H
#define MICROPROCESADOR_H


using namespace std;

SC_MODULE (MicroP){

	sc_in<bool> clock;

	Fetch* fetch;
	Pipe* pipe1;
	Register_F* regf;
	Pipe2* pipe2;
	Execute* exec;
	Pipe2* pipe3;

	sc_in<bool> enable_wb;
	sc_in< sc_uint<R_size> > dir_Wback;
	sc_in< sc_uint<Dat_size> > dat_Wback;

	sc_out< sc_uint<R_size> > op;
	sc_out< sc_uint<Dat_size> > r1, r2, result;

	sc_signal<bool> enable_sg;
	sc_signal< sc_uint<Dat_size> > inst, r1_sg1, r2_sg1, r3_sg1;
	sc_signal< sc_uint<Dat_size> > r1_sg2, r2_sg2, r3_sg2, r1_sg3, r2_sg3, r3_sg3;
	sc_signal< sc_uint<R_size> > op_sg, r1_sg, r2_sg, r3_sg, op_sg1, op_sg2, op_sg3;
	

	SC_CTOR (MicroP) 
	{
		fetch = new Fetch("fetch");
		pipe1 = new Pipe("pipe1");
		regf = new Register_F("regf");
		pipe2 = new Pipe2("pipe2");
		exec = new Execute("exec");
		pipe3 = new Pipe2("pipe3");


		//FETCH
		fetch->clk(clock);
		fetch->enable(enable_sg);
		fetch->instruction(inst);

		//PIPE ONE
		pipe1->clock(clock);
		pipe1->enable(enable_sg);
		pipe1->instruction(inst);

		pipe1->op(op_sg);
		pipe1->r1(r1_sg);
		pipe1->r2(r2_sg);
		pipe1->r3(r3_sg);
		
		//INSTRUCTION DECODING
		regf->clock(clock);
		regf->enable_wb(enable_wb);
		regf->op(op_sg);
		regf->r1(r1_sg);
		regf->r2(r2_sg);
		regf->r3(r3_sg);
		regf->dir_Wback(dir_Wback);
		regf->dat_Wback(dat_Wback);

		regf->op_out(op_sg1);
		regf->r1_out(r1_sg1);
		regf->r2_out(r2_sg1);
		regf->r3_out(r3_sg1);

		//PIPE TWO
		pipe2->clock(clock);
		pipe2->op_in(op_sg1);
		pipe2->r1_in(r1_sg1);
		pipe2->r2_in(r2_sg1);
		pipe2->r3_in(r3_sg1);
		
		pipe2->op_out(op_sg2);
		pipe2->r1_out(r1_sg2);
		pipe2->r2_out(r2_sg2);
		pipe2->r3_out(r3_sg2);

		//EXECUTE
		exec->clock(clock);
		exec->op(op_sg2);
		exec->r1(r1_sg2);
		exec->r2(r2_sg2);
		exec->r3(r3_sg2);
		
		exec->op_out(op_sg3);
		exec->r1_out(r1_sg3);
		exec->r2_out(r2_sg3);
		exec->r3_out(r3_sg3);

		//PIPE THREE
		pipe3->clock(clock);
		pipe3->op_in(op_sg3);
		pipe3->r1_in(r1_sg3);
		pipe3->r2_in(r2_sg3);
		pipe3->r3_in(r3_sg3);
		
		pipe3->op_out(op);
		pipe3->r1_out(r1);
		pipe3->r2_out(r2);
		pipe3->r3_out(result);

		sensitive<<clock.neg();
	}

	~MicroP(){
		delete fetch;
		delete pipe1;
		delete regf;
		delete pipe2;
		delete exec;
		delete pipe3;

	}

};
#endif // MICROPROCESADOR_H
