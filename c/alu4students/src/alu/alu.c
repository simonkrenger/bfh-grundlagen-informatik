/* 
 alu.c
 - 21.11.05/BHO1
 bho1 29.12.2006
 bho1 6.12.2007
 bho1 30.11.2007 - clean up
 bho1 24.11.2009 - assembler instruction
 bho1 3.12.2009 - replaced adder with full_adder
 bho1 20.7.2011 - rewrite: minimize global vars, ALU-operations are modeled with ftc taking in/out register as parameter
 bho1 6.11.2011 - rewrite flags: adding flags as functional parameter. Now alu is truly a function


 GPL applies

 Simon Krenger
 */

#include <stdio.h>
#include <string.h>

#include "alu.h"
#include "alu-opcodes.h"
#include "register.h"
#include "flags.h"
int const max_mue_memory = 100;

char mue_memory[100] = "100 Byte - this memory is at your disposal"; /*mue-memory */
char* m = mue_memory;

unsigned int c = 0; /* carry bit address    */
unsigned int s = 1; /* sum bit address      */
unsigned int c_in = 2; /* carry in bit address */

/*
 testet ob alle bits im akkumulator auf null gesetzt sind.
 Falls ja wird 1 returniert, ansonsten 0
 */
int zero_test(char accumulator[]) {
	int i;
	for (i = 0; accumulator[i] != '\0'; i++) {
		if (accumulator[i] != '0')
			return 0;
	}
	return 1;
}

/*
 Halfadder: addiert zwei character p,q und schreibt in
 den Mue-memory das summen-bit und das carry-bit.
 */
void half_adder(char p, char q) {
	char _p = p - 48;
	char _q = q - 48;
	m[s] = (_p ^ _q) + 48;
	m[c] = (_p & _q) + 48;
}

/* 
 void adder(char pbit, char qbit, char cbit)
 Adder oder auch Fulladder:
 Nimmt zwei character bits und ein carry-character-bit
 und schreibt das Resultat (summe, carry) in den Mue-speicher
 */
void full_adder(char pbit, char qbit, char cbit) {


}

/*
 Invertieren der Character Bits im Register reg
 */
void one_complement(char reg[]) {
	int i;
	for (i = 0; reg[i] != '\0'; i++) {
		if (reg[i] == '1')
			reg[i] = '0';
		else
			reg[i] = '1';
	}
}

/*
 Das zweier-Komplement des Registers reg wird in reg geschrieben
 reg := K2(reg)
 */
void two_complement(char reg[]) {
	//your code here
}

/*
 Die Werte in Register rega und Register regb werden addiert, das
 Resultat wird in Register accumulator geschrieben. Die Flags cflag,
 oflag, zflag und sflag werden entsprechend gesetzt

 accumulator := rega + regb
 */
void op_add(char rega[], char regb[], char accumulator[], char flags[]) {
	//your code here
}

/*

 ALU_OP_ADD_WITH_CARRY

 Die Werte des carry-Flags und der Register rega und
 Register regb werden addiert, das
 Resultat wird in Register accumulator geschrieben. Die Flags cflag,
 oflag, zflag und sflag werden entsprechend gesetzt

 accumulator := rega + regb + carry-flag

 */
void op_addc(char rega[], char regb[], char accumulator[], char flags[]) {
	//your code here
}

/*
 Die Werte in Register rega und Register regb werden subtrahiert, das
 Resultat wird in Register accumulator geschrieben. Die Flags cflag,
 oflag, zflag und sflag werden entsprechend gesetzt

 accumulator := rega - regb
 */
void op_sub(char rega[], char regb[], char accumulator[], char flags[]) {
	//your code here
}

/*
 Die Werte in Register rega und Register regb werden logisch geANDet, das
 Resultat wird in Register accumulator geschrieben. Die Flags cflag,
 oflag, zflag und sflag werden entsprechend gesetzt

 accumulator := rega AND regb
 */
void op_and(char rega[], char regb[], char accumulator[], char flags[]) {
	//your code here
}
/*
 Die Werte in Register rega und Register regb werden logisch geORt, das
 Resultat wird in Register accumulator geschrieben. Die Flags cflag,
 oflag, zflag und sflag werden entsprechend gesetzt

 accumulator := rega OR regb
 */
void op_or(char rega[], char regb[], char accumulator[], char flags[]) {
	//your code here
}
/*
 Die Werte in Register rega und Register regb werden logisch geXORt, das
 Resultat wird in Register accumulator geschrieben. Die Flags cflag,
 oflag, zflag und sflag werden entsprechend gesetzt

 accumulator := rega XOR regb
 */
void op_xor(char rega[], char regb[], char accumulator[], char flags[]) {
	//your code here
}

/*
 Einer-Komplement von Register rega
 rega := not(rega)
 */
void op_not_a(char rega[], char regb[], char accumulator[], char flags[]) {
	//your code here
}

/* Einer Komplement von Register regb */
void op_not_b(char rega[], char regb[], char accumulator[], char flags[]) {
	//your code here
}

/*
 Negation von Register rega
 rega := -rega
 */
void op_neg_a(char rega[], char regb[], char accumulator[], char flags[]) {
	//your code here
}

/*
 Negation von Register regb
 regb := -regb
 */
void op_neg_b(char rega[], char regb[], char accumulator[], char flags[]) {
	//your code here
}

/*
 clear mue_memory
 */
void alu_reset() {
	int i;

	for (i = 0; i < max_mue_memory; i++)
		m[i] = '0';
}

/*
 alu function
 Needed register are already alocated and may be modified
 mainly a switchboard

 alu_fct(int opcode, char reg_in_a[], char reg_in_b[], char reg_out_accu[], char flags[])

 */
void alu(unsigned int alu_opcode, char reg_in_a[], char reg_in_b[],
		char reg_out_accu[], char flags[]) {

	switch (alu_opcode) {
	case ALU_OP_ADD:
		op_add(reg_in_a, reg_in_b, reg_out_accu, flags);
		break;
	case ALU_OP_ADD_WITH_CARRY:
		op_addc(reg_in_a, reg_in_b, reg_out_accu, flags);
		break;
	case ALU_OP_SUB:
		op_sub(reg_in_a, reg_in_b, reg_out_accu, flags);
		break;
	case ALU_OP_AND:
		op_and(reg_in_a, reg_in_b, reg_out_accu, flags);
		break;
	case ALU_OP_OR:
		op_or(reg_in_a, reg_in_b, reg_out_accu, flags);
		break;
	case ALU_OP_XOR:
		op_xor(reg_in_a, reg_in_b, reg_out_accu, flags);
		break;
	case ALU_OP_NEG_A:
		op_neg_a(reg_in_a, reg_in_b, reg_out_accu, flags);
		break;
	case ALU_OP_NEG_B:
		op_neg_b(reg_in_a, reg_in_b, reg_out_accu, flags);
		break;
	case ALU_OP_NOT_A:
		op_not_a(reg_in_a, reg_in_b, reg_out_accu, flags);
		break;
	case ALU_OP_NOT_B:
		op_not_b(reg_in_a, reg_in_b, reg_out_accu, flags);
		break;
	case ALU_OP_RESET:
		alu_reset();
		break;
	default:
		printf("ALU(%i): Invalide operation %i selected", alu_opcode,
				alu_opcode);
		break;
	}
}
