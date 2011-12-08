/*
  6502_cpu-util.h
  bho1 11.7.2011
  
*/

void cpu_6502_register_dump(char* fname);

//convert bitstring <bitstr> from bit <start> to bit <end> into integer
int conv_bitstr2int(char *bitstr, unsigned int start, unsigned int end);


void set_rw2read();

void set_rw2write();


void inc_pc();
void inc_register(char* reg);
void dec_register(char* reg);
