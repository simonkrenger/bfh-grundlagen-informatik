/*
  6502-cpu.h
  bho1 12.7.2011
  GPL
*/

#ifndef _6502_CPU_H_
#define _6502_CPU_H_

#define ADDR_WIDTH 16


typedef char* cpu_register;


void set_rw2read();
void set_rw2write();
/*
  Registers used in 6502 CPU
*/

/*
  hidden register
*/
// Databus Register, shared with memory.c
//extern char *databus_register;
extern char *dbr;

// Addressbus Register Low byte, shared with memory.c
extern char *abrl;
// Addressbus Register High byte, shared with memory.c
extern char *abrh;
// Read/Write bit
extern char read_write;
//Instruction Register
extern char *ir;

/*
  User register
*/
// Accumulator
extern char *acc;

// index register
extern char *idx;
extern char *idy
;
//stack pointer SP
extern char *sp;

//programm counter
extern char *pcl;
extern char *pch;

//flags
extern char *flags;

// ultra helpers
extern char *zero, *one;

// intialize 6502 cpu
void cpu_6502_reset();

void fetch();

void *decode();

void trace();

void execute(void (*fct)());

void fetch_decode_execute_cycle();

void cpu_6502_init();

#endif 
/* _6502_CPU_H_ */
