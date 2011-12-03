;;
;;; hello-world.asm
;;; compile with
;;; 64tass hello-world.asm -o hello-world
;;; or
;;; make hello-world
;;; Programmstart mit SYS 49152
;;; 
*=$c000
	LDY #$00 
L0 
	LDA L1,Y 
	CMP #0 
	BEQ L2 
	JSR $FFD2 
	INY 
	JMP L0 
L1 
	.byte "HELLO WORLD",0
L2
	RTS 
