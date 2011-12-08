/*
  register.c
  bho1 2006
  bho1 2007
  GPL
*/
#include <ctype.h>
#include <stdio.h>

#include "register.h"
#include "alu.h"


void ldhex2regnibble(char hexcode, char* regnibble){
	
	switch (tolower(hexcode)){
	case '0':
		*regnibble++ = '0';
		*regnibble++ = '0';
		*regnibble++ = '0';
		*regnibble = '0';
		break;
	case '1':
		*regnibble =   '0';
		*(regnibble+1) = '0';
		*(regnibble+2) = '0';
		*(regnibble+3) = '1';
		break;
	case '2':
		*regnibble =   '0';
		*(regnibble+1) = '0';
		*(regnibble+2) = '1';
		*(regnibble+3) = '0';
		break;
	case '3':
		*regnibble =   '0';
		*(regnibble+1) = '0';
		*(regnibble+2) = '1';
		*(regnibble+3) = '1';
		break;
	case '4':
		*regnibble =   '0';
		*(regnibble+1) = '1';
		*(regnibble+2) = '0';
		*(regnibble+3) = '0';
		break;
	case '5':
		*regnibble =   '0';
		*(regnibble+1) = '1';
		*(regnibble+2) = '0';
		*(regnibble+3) = '1';
		break;
	case '6':
		*regnibble =   '0';
		*(regnibble+1) = '1';
		*(regnibble+2) = '1';
		*(regnibble+3) = '0';
		break;
	case '7':
		*regnibble =   '0';
		*(regnibble+1) = '1';
		*(regnibble+2) = '1';
		*(regnibble+3) = '1';
		break;
	case '8':
		*regnibble =   '1';
		*(regnibble+1) = '0';
		*(regnibble+2) = '0';
		*(regnibble+3) = '0';
		break;
	case '9':
		*regnibble =   '1';
		*(regnibble+1) = '0';
		*(regnibble+2) = '0';
		*(regnibble+3) = '1';
		break;
	case 'a' :
		*regnibble =   '1';
		*(regnibble+1) = '0';
		*(regnibble+2) = '1';
		*(regnibble+3) = '0';
		break;
	case 'b' :
		*regnibble =   '1';
		*(regnibble+1) = '0';
		*(regnibble+2) = '1';
		*(regnibble+3) = '1';
		break;
	case 'c' :
		*regnibble =   '1';
		*(regnibble+1) = '1';
		*(regnibble+2) = '0';
		*(regnibble+3) = '0';
		break;
	case 'd' :
		*regnibble =   '1';
		*(regnibble+1) = '1';
		*(regnibble+2) = '0';
		*(regnibble+3) = '1';
		break;
	case 'e' :
		*regnibble =   '1';
		*(regnibble+1) = '1';
		*(regnibble+2) = '1';
		*(regnibble+3) = '0';
		break;
	case 'f' :
		*regnibble =   '1';
		*(regnibble+1) = '1';
		*(regnibble+2) = '1';
		*(regnibble+3) = '1';
		break;
	}
}

void ldhex2register(char* hexcode, char* reg){
	switch(REG_WIDTH){
		case 8:
			ldhex2regnibble(*hexcode, reg);
			ldhex2regnibble(*(hexcode+1), reg+4);
			break;
		case 16:
			ldhex2regnibble(*hexcode, reg);
			ldhex2regnibble(*(hexcode+1), reg+4);
			ldhex2regnibble(*(hexcode+2), reg+8);
			ldhex2regnibble(*(hexcode+3), reg+12);
			break;
	}
}

void print_reg(char* reg)
{
  printf("%s", reg);
  printf("\n");
}

void cp_register(char *r1, char *r2){
  int i;
  for(i=0; i<REG_WIDTH; i++)
    r2[i] = r1[i];
}

