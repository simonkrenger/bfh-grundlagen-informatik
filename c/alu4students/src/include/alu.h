/*
 alu.h

 bho1 2006
 initial

 bho1 28.12.2006
 bho1 29.11.2008

 bho1 30.10.2011
 * added get flags functions declarations
 'cause they are needed in alu-main.c
 * fct alu now reflecting procedural aspect,
 works with side-effect on entered data
 * changed print_alu: we ain't no flags register parameter anymore

 bho1 6.11.2011
 * flags now is parametrized

 GPL applies
 */

#ifndef _ALU_HEADER_
#define _ALU_HEADER_

#include "alu-opcodes.h"

char getCarryflag(char flags[]);
char getSignflag(char flags[]);
char getZeroflag(char flags[]);
char getOverflowflag(char flags[]);

void alu(unsigned int alu_opcode, char reg_in_a[], char reg_in_b[],
		char reg_out_accu[], char flags[]);

void print_alu(char *rega, char *regb, char * accumulator, char flags[]);

#endif /* _ALU_H_ */

