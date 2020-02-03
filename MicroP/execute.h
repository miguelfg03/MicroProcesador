#ifndef EXECUTE_H
#define EXECUTE_H

enum instruction {LOAD, STORE, ADD, SUB, MULT, DIV, MAYOR, 
									MENOR, EQUAL, AND, OR,NOT,JUMPZ};

class Execute : public sc_module {

  public:
  
    sc_in <bool> clock;
 		
    sc_in < sc_uint<R_size> > op;
		sc_in < sc_uint<Dat_size> > r1, r2, r3;

    sc_out < sc_uint<R_size> > op_out;
		sc_out < sc_uint<Dat_size> >r1_out, r2_out, r3_out;
    
    SC_CTOR(Execute)
  {
    SC_METHOD(operation);
      sensitive << clock.neg() << op << r1 << r2;

  }

    void operation()
		{
				op_out.write(op.read());
				r1_out.write(r1.read());	
				r2_out.write(r2.read());
	
       switch (op.read())
        {
            case LOAD:
								r3_out.write(r3.read());
						break;
    
            case STORE:
								r3_out.write(r3.read());
            break;

            case ADD:
								r3_out.write(r1.read() + r2.read());
						break;

            case SUB:
								r3_out.write(r1.read() - r2.read());
            break;

            case MULT:
								r3_out.write(r1.read() * r2.read());
            break;

            case DIV:
                r3_out.write(r1.read() / r2.read());
            break;

						case MAYOR:
								if(r1.read() > r2.read())
                		r3_out.write(r1.read());
								else 
										r3_out.write(r2.read());
            break;

						case MENOR:
								if(r1.read() < r2.read())
                		r3_out.write(r1.read());
								else 
										r3_out.write(r2.read());
            break;

						case EQUAL:
								if(r1.read() == r2.read())
                		r3_out.write(r1.read());
								else 
										r3_out.write(r3.read());
            break;

            case AND:
            		r3_out.write(r1.read() and r2.read());
            break;

            case OR:
								r3_out.write(r1.read() or r2.read());
            break;

						 case NOT:
            		r3_out.write(not r3.read());
            break;

						 case JUMPZ:
                if(r3_out.read() == 0){  
                	r3_out.write(r3.read());
								}
            break;

            default:
                r3_out.write(0);
            		break;
        }
		}
};
#endif //EXECUTE_H
