/* 
 flags.c
 bho1: 26.11.2011 init

 */

#include "register.h"

void clearCarryflag(char flags[]) {
	flags[REG_WIDTH - 1] = '0';
}
void setCarryflag(char flags[]) {
	flags[REG_WIDTH - 1] = '1';
}
char getCarryflag(char flags[]) {
	return flags[REG_WIDTH - 1];
}
void clearZeroflag(char flags[]) {
	flags[REG_WIDTH - 2] = '0';
}
void setZeroflag(char flags[]) {
	flags[REG_WIDTH - 2] = '1';
}
char getZeroflag(char flags[]) {
	return flags[REG_WIDTH - 2];
}
void clearIRQflag(char flags[]) {
	flags[REG_WIDTH - 3] = '0';
}
void setIRQflag(char flags[]) {
	flags[REG_WIDTH - 3] = '1';
}
char getIRQflag(char flags[]) {
	return flags[REG_WIDTH - 3];
}
void clearDflag(char flags[]) {
	flags[REG_WIDTH - 4] = '0';
}
void setDflag(char flags[]) {
	flags[REG_WIDTH - 4] = '1';
}
char getDflag(char flags[]) {
	return flags[REG_WIDTH - 4];
}
void clearBRKflag(char flags[]) {
	flags[REG_WIDTH - 5] = '0';
}
void setBRKflag(char flags[]) {
	flags[REG_WIDTH - 5] = '1';
}
char getBRKflag(char flags[]) {
	return flags[REG_WIDTH - 5];
}
void clearOverflowflag(char flags[]) {
	flags[REG_WIDTH - 7] = '0';
}
void setOverflowflag(char flags[]) {
	flags[REG_WIDTH - 7] = '1';
}
char getOverflowflag(char flags[]) {
	return flags[REG_WIDTH - 7];
}
void clearSignflag(char flags[]) {
	flags[REG_WIDTH - 8] = '0';
}
void setSignflag(char flags[]) {
	flags[REG_WIDTH - 8] = '1';
}
char getSignflag(char flags[]) {
	return flags[REG_WIDTH - 8];
}
