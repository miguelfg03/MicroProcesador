#include <systemc.h>
#include <iostream>

#include <Fetch.h>
#include <Pipe.h>
#include <register_file.h>
#include <Pipe2.h>
#include <execute.h>
#include <Pipe3.h>
#include <Pipe4.h>
#include <memory.h>
#include<macros.h>

#ifndef MICROPROCESADOR_H
#define MICROPROCESADOR_H


using namespace std;

SC_MODULE (MicroP){

	sc_in<bool> clock;

	sc_out< sc_uint<Dat_size> > data;


	Fetch* fetch;
	Pipe* pipe1;
	Register_F* regf;
	Pipe2* pipe2;
	Execute* exec;
	Pipe3* pipe3;
	Mem_A* mem_a;
	Pipe4* pipe4;

	sc_signal<bool> enable_sg, e_sg,e_sg1, e_sg2, enable_wb;

	sc_signal< sc_uint<R_size> > dir_Wback, r1_sg, r2_sg, r3_sg, r1_sg1, r1_sg2;
	sc_signal< sc_uint<R_size> > op_s, op_sg, op_sg3,op_sg1, op_sg2, dir_sg;
	sc_signal< sc_uint<R_size> > dir_sg1, dir_sg2, dir_sg3;

	sc_signal< sc_uint<Instruction_size> > inst;
	sc_signal< sc_uint<Dat_size> > r3_sg1,r2_sg1,r3_sg2, r2_sg2, dat_Wback, r_sg, data_sg, dat_sg;

	sc_signal< sc_uint<Dir_mem_size> > dir_mem_sg, dir_mem_sg2, dir_mem_sg3;


	SC_CTOR (MicroP) 
	{
		fetch = new Fetch("fetch");
		pipe1 = new Pipe("pipe1");
		regf = new Register_F("regf");
		pipe2 = new Pipe2("pipe2");
		exec = new Execute("exec");
		pipe3 = new Pipe3("pipe3");
		mem_a = new Mem_A("mem_a");
		pipe4 = new Pipe4("pipe4");


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
		pipe1->dir_mem(dir_mem_sg);
		
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
		pipe2->dir_mem_in(dir_mem_sg);

		pipe2->op_out(op_sg2);
		pipe2->r1_out(r1_sg2);
		pipe2->r2_out(r2_sg2);
		pipe2->r3_out(r3_sg2);
		pipe2->dir_mem(dir_mem_sg2);

		//EXECUTE
		exec->clock(clock);
		exec->op(op_sg2);
		exec->r1(r1_sg2);
		exec->r2(r2_sg2);
		exec->r3(r3_sg2);
		
		exec->dir_out(dir_sg);
		exec->r_out(r_sg);
		exec->enable(e_sg);

		//PIPE THREE
		pipe3->clock(clock);
		pipe3->op_in(op_s);
		pipe3->data_in(r_sg);
		pipe3->dir_in(dir_sg);
		pipe3->enable_in(e_sg);
		pipe3->dir_mem_in(dir_mem_sg2);
		
		pipe3->data_out(data_sg);
		pipe3->op_out(op_sg3);
		pipe3->dir_out(dir_sg1);
		pipe3->enable_out(e_sg1);
		pipe3->dir_mem(dir_mem_sg3);

		//MEMORY ACCESS
		mem_a->clk(clock);
		mem_a->op(op_sg3);
		mem_a->enable(e_sg1);
		mem_a->dir_in(dir_mem_sg3);
		mem_a->data_in(data_sg);

		mem_a->data_out(dat_sg);
		mem_a->enable_out(e_sg2);

		//PIPE FOUR
		pipe4->clock(clock);
		pipe4->data_in(dat_sg);
		pipe4->dir_in(dir_sg3);
		pipe4->enable_in(e_sg2);

		pipe4->data_out(dat_Wback);
		pipe4->dir_out(dir_Wback);
		pipe4->enable_out(enable_wb);
	
		SC_METHOD(fun);
			sensitive << dat_Wback;

		SC_METHOD(prop_pipe3)
      		sensitive << dir_sg1;

		SC_METHOD(prop_pipe2)
      		sensitive << op_sg2;
	}

	 void fun()
   {
		data.write(dat_Wback.read());     
   }

	void prop_pipe2(){
		op_s = op_sg2;
	}

	void prop_pipe3()
	{
		dir_sg3 = dir_sg1;
	}

	~MicroP(){
		delete fetch;
		delete pipe1;
		delete regf;
		delete pipe2;
		delete exec;
		delete pipe3;
		delete mem_a;
		delete pipe4;
	}

};
#endif // MICROPROCESADOR_H
