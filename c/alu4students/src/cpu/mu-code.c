/*
 * mu-code.c
 *
 * Last change: Jan 18, 2012
 *      Author: Simon Krenger <krens1@bfh.ch>
 */
#include <stdio.h>
#include <string.h>

#include "mu-code.h"
#include "cpu.h"
#include "alu.h"
#include "register.h"

struct cpu6502 {
	// PC low byte / PC high byte
	char *pcl;
	char *pch;

	// Accumulator A register
	char *acc;

	// Index registers
	char *idx;
	char *idy;

	// Stack pointer
	char *sp;

	// Flags
	char *flags;

	// Index register
	char *ir;

	// Data bus register
	char *dbr;

	// Adr. bus
	char *abrl;
	char *abrh;
};

/**
 * Function provided by the teacher
 */
void cpu_6502_lda_imm(struct cpu6502 *cpu) {
	cp_register(cpu->pcl, cpu->abrl);
	cp_register(cpu->pch, cpu->abrh);

	set_rw2read();
	access_memory();

	cp_register(cpu->dbr, cpu->acc);

	if (cpu->acc == '1')
		setSignflag(cpu->flags);
	else
		clearSignflag(cpu->flags);

	int i;
	setZeroflag(cpu->flags);
	for (i = 0; i < REG_WIDTH; i++) {
		if (cpu->acc[i] == '1') {
			clearZeroflag(cpu->flags);
			break;
		}
	}

	inc_pc();

}

/**
 * Absolute addressing
 *
 * A full 16-bit address is specified and the byte at that address is used to
 * perform the computation.
 */
void cpu_6502_lda_absolute(struct cpu6502 *cpu) {

	// Get low byte
	cp_register(cpu->pcl, cpu->abrl);
	cp_register(cpu->pch, cpu->abrh);

	set_rw2read();
	access_memory();

	char low_byte[REG_WIDTH + 1];
	cp_register(cpu->dbr, &low_byte);

	// Get high byte
	inc_pc();
	cp_register(cpu->pcl, cpu->abrl);
	cp_register(cpu->pch, cpu->abrh);

	set_rw2read();
	access_memory();

	// Set the address to what we just read
	cp_register(cpu->dbr, cpu->abrh);
	cp_register(&low_byte, cpu->abrl);

	set_rw2read();
	access_memory();

	// Retrieve the byte
	cp_register(cpu->dbr, cpu->acc);

	// Set flags
	if (cpu->acc == '1')
		setSignflag(cpu->flags);
	else
		clearSignflag(cpu->flags);

	int i;
	setZeroflag(cpu->flags);
	for (i = 0; i < REG_WIDTH; i++) {
		if (cpu->acc[i] == '1') {
			clearZeroflag(cpu->flags);
			break;
		}
	}

	// Next instruction
	inc_pc();
}

/**
 * Absolute addressing with index
 *
 * The address to be accessed by an instruction using Y register indexed
 * absolute addressing is computed by taking the 16 bit address from the
 * instruction and added the contents of the Y register.
 */
void cpu_6502_lda_absolute_y(struct cpu6502 *cpu) {

	// Get low byte
	cp_register(cpu->pcl, cpu->abrl);
	cp_register(cpu->pch, cpu->abrh);

	set_rw2read();
	access_memory();

	char low_byte[REG_WIDTH + 1];
	cp_register(cpu->dbr, &low_byte);

	// Get high byte
	inc_pc();
	cp_register(cpu->pcl, cpu->abrl);
	cp_register(cpu->pch, cpu->abrh);

	set_rw2read();
	access_memory();

	char high_byte[REG_WIDTH + 1] = "00000000";
	cp_register(cpu->dbr, &high_byte);

	// Add Y to address (low byte first)
	// Directly write the results into the address bus registers
	op_add(cpu->idy, low_byte, cpu->abrl, cpu->flags);
	if(getCarryflag(cpu->flags) == '1')
		op_addc("00000000", high_byte, cpu->abrh, cpu->flags);
	else
		cp_register(&high_byte, cpu->abrh);

	// Read from address bus
	set_rw2read();
	access_memory();
	cp_register(cpu->dbr, cpu->acc);

	// Set flags
	if (cpu->acc == '1')
		setSignflag(cpu->flags);
	else
		clearSignflag(cpu->flags);

	int i;
	setZeroflag(cpu->flags);
	for (i = 0; i < REG_WIDTH; i++) {
		if (cpu->acc[i] == '1') {
			clearZeroflag(cpu->flags);
			break;
		}
	}

	// Next instruction
	inc_pc();
}

/**
 * Indexed indirect addressing
 *
 * Indexed indirect addressing is normally used in conjunction with a table of
 * address held on zero page. The address of the table is taken from the
 * instruction and the X register added to it (with zero page wrap around) to
 * give the location of the least significant byte of the target address.
 */
void cpu_6502_lda_index_ind(struct cpu6502 *cpu) {

	// Get low byte
	cp_register(cpu->pcl, cpu->abrl);
	cp_register(cpu->pch, cpu->abrh);

	set_rw2read();
	access_memory();

	char low_byte[REG_WIDTH + 1];
	cp_register(cpu->dbr, &low_byte);

	// Add X to address, write results directly to address bus registers
	op_add(cpu->idx, low_byte, cpu->abrl, cpu->flags);

	char high_byte[REG_WIDTH + 1] = "00000000";
	if(getCarryflag(cpu->flags) == '1')
		op_addc("00000000", high_byte, cpu->abrh, cpu->flags);
	else
		cp_register(&high_byte, cpu->abrh);

	// At this point, we have the address of the address

	// Get low byte of address
	set_rw2read();
	access_memory();

	cp_register(cpu->dbr, low_byte);

	// Get high byte of address
	inc_pc();
	cp_register(cpu->pcl, cpu->abrl);
	cp_register(cpu->pch, cpu->abrh);

	set_rw2read();
	access_memory();

	// Now we have what we need, get the actual value
	cp_register(cpu->dbr, cpu->abrh);
	cp_register(low_byte, cpu->abrl);

	set_rw2read();
	access_memory();

	cp_register(cpu->dbr, cpu->acc);

	// Set flags
	if (cpu->acc == '1')
		setSignflag(cpu->flags);
	else
		clearSignflag(cpu->flags);

	int i;
	setZeroflag(cpu->flags);
	for (i = 0; i < REG_WIDTH; i++) {
		if (cpu->acc[i] == '1') {
			clearZeroflag(cpu->flags);
			break;
		}
	}

	// Next instruction
	inc_pc();
}
