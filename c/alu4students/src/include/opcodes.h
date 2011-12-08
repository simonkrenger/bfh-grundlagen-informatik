/*
  opcodes.h

  bo
  bho1 10.12.2009 Could do some pretty print with awk '$1 ~ /^#define/ { printf <etc.> }'
*/

/*
  Move Befehle
 */
#define CPU_OPCODE_MOV_REGISTER_DIREKT_REGISTER_DIREKT 0 // 00 0b000000
#define CPU_OPCODE_MOV_REGISTER_DIREKT_REGISTER_INDIREKT 1 // 0x1 0b000001
#define CPU_OPCODE_MOV_REGISTER_DIREKT_ADDRESS 2 // 0x2 0b000010
#define CPU_OPCODE_MOV_REGISTER_INDIREKT_REGISTER_DIREKT 3 // 0x3 0b000011
#define CPU_OPCODE_MOV_REGISTER_INDIREKT_REGISTER_INDIREKT 4 // 0x4 0b000100
#define CPU_OPCODE_MOV_REGISTER_INDIREKT_ADDRESS 5 // 0x5 0b000101
#define CPU_OPCODE_MOV_ADDRESS_REGISTER_DIREKT 6 // 0x6 0b000110
#define CPU_OPCODE_MOV_ADDRESS_REGISTER_INDIREKT 7 // 0x7 0b000111
#define CPU_OPCODE_MOV_ADDRESS_ADDRESS 8 // 0x8 0b001000
#define CPU_OPCODE_MOV_IMMEDIATE_REGISTER 9 // 0x9 0b001001
#define CPU_OPCODE_MOV_IMMEDIATE_REGISTER_INDIREKT 10 // 0xa 0b001010
#define CPU_OPCODE_MOV_IMMEDIATE_ADDRESS 11 // 0xb 0b001011

/*
  Logische Befehle
*/
#define CPU_OPCODE_AND 12 // 0xc 0b001100
#define CPU_OPCODE_OR 13 // 0xd 0b001101
#define CPU_OPCODE_XOR 14 // 0xe 0b001110
#define CPU_OPCODE_NOT 15 // 0xf 0b001111

/*
  Jump Befehle
*/

//Unconditional Jump
#define CPU_OPCODE_JMP 16 // 0x10 0b010000

//Conditional Jump
#define CPU_OPCODE_JCC 17 // 0x11 0b010001

//Flag Jump
#define CPU_OPCODE_JF 18 // 0x12 0b010010
#define CPU_OPCODE_JNF 19 // 0x13 0b010011

//Signed Relative Jump
#define CPU_OPCODE_JR 20 // 0x14 0b010100

/*
  Arithmetische Befehle
 */
#define CPU_OPCODE_ADD 21 // 0x15 0b010101
#define CPU_OPCODE_SUB 22 // 0x16 0b010110
#define CPU_OPCODE_ADC 23 // 0x17 0b010111
#define CPU_OPCODE_SBB 24 // 0x18 0b011000
#define CPU_OPCODE_INC 25 // 0x19 0b011001
#define CPU_OPCODE_DEC 26 // 0x1a 0b011010
#define CPU_OPCODE_NEG 27 // 0x1b 0b011011
#define CPU_OPCODE_CMP 28 // 0x1c 0b011100

/*
  Stack Befehle
*/
#define CPU_OPCODE_PUSH 29 // 0x1d 0b011101
#define CPU_OPCODE_POP 30 // 0x1e 0b011110
#define CPU_OPCODE_CALL 31 // 0x1f 0b011111
#define CPU_OPCODE_RET 32 // 0x20 0b100000

/*
  Gemischte Befehle
*/
#define CPU_OPCODE_RESET 33 // 0x21 0b100001
#define CPU_OPCODE_SHIFT 34 // 0x22 0b100010
#define CPU_OPCODE_ROTATE 35 // 0x23 0b100011
#define CPU_OPCODE_NOP 36 // 0x24 0b100100
#define CPU_OPCODE_HALT 37 // 0x25 0b100101

/*
  Register
*/
#define CPU_OPCODE_AX 0
#define CPU_OPCODE_BX 1
#define CPU_OPCODE_CX 2
#define CPU_OPCODE_DX 3

/*
  Condition Codes cc
*/
#define CPU_OPCODE_CC_A 0 // 00 0b00000
#define CPU_OPCODE_CC_NBE 1 // 0x1 0b00001
#define CPU_OPCODE_CC_AE 2 // 0x2 0b00010
#define CPU_OPCODE_CC_NB 3 // 0x3 0b00011
#define CPU_OPCODE_CC_B 4 // 0x4 0b00100
#define CPU_OPCODE_CC_NAE 5 // 0x5 0b00101
#define CPU_OPCODE_CC_BE 6 // 0x6 0b00110
#define CPU_OPCODE_CC_NA 7 // 0x7 0b00111
#define CPU_OPCODE_CC_E 8 // 0x8 0b01000
#define CPU_OPCODE_CC_G 9 // 0x9 0b01001
#define CPU_OPCODE_CC_NLE 10 // 0xa 0b01010
#define CPU_OPCODE_CC_GE 11 // 0xb 0b01011
#define CPU_OPCODE_CC_NL 12 // 0xc 0b01100
#define CPU_OPCODE_CC_L 13 // 0xd 0b01101
#define CPU_OPCODE_CC_NGE 14 // 0xe 0b01110
#define CPU_OPCODE_CC_LE 15 // 0xf 0b01111
#define CPU_OPCODE_CC_NG 16 // 0x10 0b10000
#define CPU_OPCODE_CC_NE 17 // 0x11 0b10001

/*
  Jump Flag Codes JFC for Jump on Flag Set
*/
#define CPU_OPCODE_JFC_C 0
#define CPU_OPCODE_JFC_Z 1
#define CPU_OPCODE_JFC_S 2
#define CPU_OPCODE_JFC_O 3

/*
  Jump Flag Codes JFC for Jump on Flag Not Set
*/
#define CPU_OPCODE_JFC_NC 0
#define CPU_OPCODE_JFC_NZ 1
#define CPU_OPCODE_JFC_NO 2
#define CPU_OPCODE_JFC_NS 3

/*
  Addressing Modes fuer Jump
*/
#define CPU_OPCODE_JMP_REGISTER_INDIREKT 0
#define CPU_OPCODE_JMP_IMMEDIATE 1

/*
  Extended Registercode
*/
#define CPU_OPCODE_XRC_AX 0
#define CPU_OPCODE_XRC_BX 1
#define CPU_OPCODE_XRC_CX 2
#define CPU_OPCODE_XRC_DX 3
#define CPU_OPCODE_XRC_PC 4 
#define CPU_OPCODE_XRC_SP 5

/*
  Flags Setting instruction
*/
#define CPU_OPCODE_SETT 38 // Must be >37 because rest is already used


