#ifndef EXECUTE_H
#define EXECUTE_H

enum instruction {LOAD = 1, STORE = 2, ADD = 3, SUB = 4, MULT = 5, DIV = 6 , MAYOR = 7, 
									MENOR = 8, EQUAL = 9, AND = 10, OR = 11,NOT = 12,JUMPZ = 13};

class Execute : public sc_module {

  public:
  
    sc_in <bool> clock;
 		
    sc_in < sc_uint<R_size> > op, r1;
	sc_in < sc_uint<Dat_size> > r2, r3;

    sc_out < sc_uint<R_size> > dir_out;
	sc_out < sc_uint<Dat_size> > r_out;
	sc_out <bool> enable;
    
    SC_CTOR(Execute)
  {
    SC_METHOD(operation);
      sensitive << clock.neg() << op << r1 << r2 << r3;

  }

    void operation()
		{

       	switch (op.read())
        {
            case LOAD:
					dir_out.write(r1.read());
					r_out.write(0);
					enable.write(false);
			break;
    
            case STORE:
					r_out.write(r2.read());
					dir_out.write(r1.read());
					enable.write(true);
            break;

            case ADD:
					r_out.write(r2.read() + r3.read());
					dir_out.write(r1.read());
					enable.write(false);
			break;

            case SUB:
					r_out.write(r2.read() - r3.read());
					dir_out.write(r1.read());
					enable.write(true);
            break;

            case MULT:
					r_out.write(r2.read()*r3.read());
					dir_out.write(r1.read());
					enable.write(true);
            break;

            case DIV:
            		r_out.write(r2.read() / r3.read());
					dir_out.write(r1.read());
					enable.write(true);
            break;

			case MAYOR:
					if(r2.read() > r3.read())
                		r_out.write(r2.read());
					else 
						r_out.write(r3.read());

					dir_out.write(r1.read());
					enable.write(true);
            break;

			case MENOR:
					if(r2.read() < r3.read())
            	  		r_out.write(r2.read());
					else 
						r_out.write(r3.read());

					dir_out.write(r1.read());
					enable.write(true);
            break;

			case EQUAL:
					if(r2.read() == r3.read())
                		r_out.write(r2.read());
					else 
						r_out.write(r3.read());

					dir_out.write(r1.read());
					enable.write(true);
            break;

            case AND:
            		r_out.write(r2.read() and r3.read());
					dir_out.write(r1.read());
					enable.write(true);
            break;

            case OR:
					r_out.write(r2.read() or r3.read());
					dir_out.write(r1.read());
					enable.write(true);
            break;

			case NOT:
            		r_out.write(not r2.read());
					dir_out.write(r1.read());
					enable.write(true);
            break;

			case JUMPZ:
            	    if(r2.read() == 0){  
                		r_out.write(r1.read());
					}
					dir_out.write(r1.read());
					enable.write(true);
            break;

            default:
                	r_out.write(0);
					dir_out.write(0);
					enable.write(false);
            break;
        }
		}
};
#endif //EXECUTE_H
