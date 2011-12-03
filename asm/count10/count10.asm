;;
;;; count10.asm
;;; compile with
;;; 64tass count10.asm -o count10
;;; or
;;; make count10
;;; Programmstart mit SYS 49152
;;; 
*=$c000

	LDY #$09
L0
	TYA
	CLC
	ADC #$30
	JSR $FFD2
	TYA
	CMP #0 
	BEQ L1
	DEY 
	JMP L0 
L1 
	RTS 
