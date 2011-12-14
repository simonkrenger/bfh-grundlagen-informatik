/**
 * alu.c
 *
 * bho1 29.12.2006
 * bho1 6.12.2007
 * bho1 30.11.2007 - clean up
 * bho1 24.11.2009 - assembler instruction
 * bho1 3.12.2009 - replaced adder with full_adder
 * bho1 20.7.2011 - rewrite: minimize global vars, ALU-operations are modeled with ftc taking in/out register as parameter
 * bho1 6.11.2011 - rewrite flags: adding flags as functional parameter. Now alu is truly a function
 *
 * GPL applies
 *
 * Simon Krenger
 */

#include <stdio.h>
#include <string.h>

#include "alu.h"
#include "alu-opcodes.h"
#include "register.h"
#include "flags.h"

#define ASCII_OFFSET 48

int const max_mue_memory = 100;

char mue_memory[100] = "100 Byte - this memory is at your disposal"; /*mue-memory */
char* m = mue_memory;

unsigned int c = 0; /* carry bit address    */
unsigned int s = 1; /* sum bit address      */
//unsigned int c_in = 2; /* carry in bit address */

/**
 * Checks if all bits in the accumulator are set to '0'.
 * If this is the case, 1 is returned, else 0 is returned.
 */
int zero_test(char accumulator[]) {
	int i;
	for (i = 0; accumulator[i] != '\0'; i++) {
		if (accumulator[i] != '0')
			return 0;
	}
	return 1;
}

/**
 * Half adder for two bits. Adds two character bits p,q
 * and writes the sum-bit and the carry-bit into the
 * mue-memory.
 */
void half_adder(char p, char q) {
	char _p = p & 1;
	char _q = q & 1;
	m[s] = (_p ^ _q) + ASCII_OFFSET;
	m[c] = (_p & _q) + ASCII_OFFSET;
}

/**
 * Full adder for two character bits and one carry-bit.
 * Implemented with two half adders. The result is stored
 * in the mue-memory (sum and carry).
 */
void full_adder(char pbit, char qbit, char cbit) {
	half_adder(pbit, qbit);
	char c1 = m[c] & 1;

	half_adder(m[s], cbit);
	m[c] = (c1 | (m[c] & 1)) + ASCII_OFFSET;
}

/**
 * Inversion of register "reg"
 */
void one_complement(char reg[]) {
	int i;
	for (i = 0; i < REG_WIDTH; i++) {
		reg[i] = (reg[i] == '1' ? '0' : '1');
	}
}

/**
 * Calculates the two's complement for a register "reg"
 * and stores the result in the register itself.
 *
 */
void two_complement(char reg[]) {
	// Two's complement is reg := NEG(reg) + 1

	one_complement(reg);

	// Since we need to add 1, use the carry-flag
	m[c] = '1';

	// Then, we basically add 0 (but remember m[c]!)
	int i;
	for (i = REG_WIDTH - 1; i >= 0; i--) {
		full_adder(reg[i], '0', m[c]);
		reg[i] = m[s];
	}
}

/**
 * ALU_OP_ADD_WITH_CARRY
 * Adds the values of registers "rega" and "regb" and writes the result
 * to register "accumulator". The carry-flag is checked. After the operation,
 * the Carry-Flag, Overflow-Flag, Zero-Flag and Sign-Flag are set accordingly.
 *
 * accumulator := rega + regb + carry-flag
 */
void op_addc(char rega[], char regb[], char accumulator[], char flags[]) {

	m[c] = getCarryflag(flags);

	int i;
	for (i = REG_WIDTH - 1; i >= 0; i--) {
		full_adder(rega[i], regb[i], m[c]);
		accumulator[i] = m[s];
	}

	// Carry flag
	m[c] == '1' ? setCarryflag(flags) : clearCarryflag(flags);

	// Overflow flag
	// Convert bits to binary 1 and 0 (for bit arithmetics)
	char a = rega[0] & 1;
	char b = regb[0] & 1;
	char c = accumulator[0] & 1;

	if (((a & b & !c) | (!a & !b & c)) + ASCII_OFFSET == '1') {
		setOverflowflag(flags);
	} else {
		clearOverflowflag(flags);
	}

	// Sign flag
	c ? setSignflag(flags) : clearSignflag(flags);

	// Zero flag
	zero_test(accumulator) ? setZeroflag(flags) : clearZeroflag(flags);
}

/**
 * ALU_OP_ADD
 *
 * Adds the values of registers "rega" and "regb" and stores the result of
 * the operation in register "accumulator". The carry-flag is ignored.
 * After the operation, the Carry-Flag, Overflow-Flag, Zero-Flag and
 * Sign-Flag are set accordingly.
 *
 * accumulator := rega + regb
 */
void op_add(char rega[], char regb[], char accumulator[], char flags[]) {
	clearCarryflag(flags);
	op_addc(rega, regb, accumulator, flags);
}

/**
 * ALU_OP_SUB
 *
 * Subtracts the register "regb" from "rega", the result is then stored
 * in the register "accumulator". After the operation, the Carry-Flag,
 * Overflow-Flag, Zero-Flag and Sign-Flag are set accordingly.
 *
 * accumulator := rega - regb
 */
void op_sub(char rega[], char regb[], char accumulator[], char flags[]) {
	// Subtraction is acc := rega + two_complement(regb)
	two_complement(regb);

	clearCarryflag(flags);
	op_addc(rega, regb, accumulator, flags);

	// Carry flag
	// Attention: Invert carry flag
	getCarryflag(flags) == '1' ? clearCarryflag(flags) : setCarryflag(flags);

}

/**
 * ALU_OP_AND
 *
 * Performs a logical AND of the registers "rega" and "regb". The result
 * is then stored in the register "accumulator". The Zero-Flag is set
 * accordingly.
 *
 * accumulator := rega AND regb
 */
void op_and(char rega[], char regb[], char accumulator[], char flags[]) {
	int i;
	for (i = 0; i < REG_WIDTH; i++) {
		accumulator[i] = ((rega[i] & 1) & (regb[i] & 1)) + ASCII_OFFSET;
	}

	// Zero flag
	zero_test(accumulator) ? setZeroflag(flags) : clearZeroflag(flags);

	// Sign flag
	accumulator[0] == '1' ? setSignflag(flags) : clearSignflag(flags);
}

/**
 * ALU_OP_OR
 *
 * Performs a logical OR of the registers "rega" and "regb". The result
 * is then stored in the register "accumulator". The Zero-Flag is set
 * accordingly.
 *
 * accumulator := rega OR regb
 */
void op_or(char rega[], char regb[], char accumulator[], char flags[]) {
	int i;
	for (i = 0; i < REG_WIDTH; i++) {
		accumulator[i] = ((rega[i] & 1) | (regb[i] & 1)) + ASCII_OFFSET;
	}

	// Zero flag
	zero_test(accumulator) ? setZeroflag(flags) : clearZeroflag(flags);

	// Sign flag
	accumulator[0] == '1' ? setSignflag(flags) : clearSignflag(flags);
}

/**
 * ALU_OP_XOR
 *
 * Performs a logical XOR of the registers "rega" and "regb". The result
 * is then stored in the register "accumulator". The Zero-Flag is set
 * accordingly.
 *
 * accumulator := rega XOR regb
 */
void op_xor(char rega[], char regb[], char accumulator[], char flags[]) {
	int i;
	for (i = 0; i < REG_WIDTH; i++) {
		accumulator[i] = ((rega[i] & 1) ^ (regb[i] & 1)) + ASCII_OFFSET;
	}

	// Zero flag
	zero_test(accumulator) ? setZeroflag(flags) : clearZeroflag(flags);

	// Sign flag
	accumulator[0] == '1' ? setSignflag(flags) : clearSignflag(flags);
}

/**
 * ALU_OP_NOT_A
 *
 * Calculates the inversion of register A ("rega")
 *
 * rega := NOT(rega)
 */
void op_not_a(char rega[], char regb[], char accumulator[], char flags[]) {
	one_complement(rega);
}

/**
 * ALU_OP_NOT_B
 *
 * Calculates the inversion of register B ("regb")
 *
 * regb := NOT(regb)
 */
void op_not_b(char rega[], char regb[], char accumulator[], char flags[]) {
	one_complement(regb);
}

/**
 * ALU_OP_NEG_A
 *
 * Negates the contents of register A ("rega")
 *
 * rega := -rega
 */
void op_neg_a(char rega[], char regb[], char accumulator[], char flags[]) {
	two_complement(rega);
}

/**
 * ALU_OP_NEG_B
 *
 * Negates the contents of register B ("regb")
 *
 * regb := -regb
 */
void op_neg_b(char rega[], char regb[], char accumulator[], char flags[]) {
	two_complement(regb);
}

/**
 * Clear mue_memory
 */
void alu_reset() {
	int i;
	for (i = 0; i < max_mue_memory; i++)
		m[i] = '0';
}

/**
 * ALU function
 * Needed registers are already allocated and may be modified.
 * This function implements a kind of switchboard
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
		printf("ALU(%i): Invalid operation %i selected", alu_opcode,
				alu_opcode);
		break;
	}
}
