;;
;;; sum.asm
;;; compile with
;;; 64tass sum.asm -o sum.prg
;;; or
;;; make sum
;;; 
;;; Load mit x64 sum.prg
;;; Programmstart mit SYS 49152
;;; 
*=$c000
;;; Warm-up:
;;; First we do an assignment:
;;; C=A+B
	LDA CellA
	CLC
	ADC CellB
	STA CellC
;;; get serious
;;; Next we sum all bytes in Arr into Sum
;;; for(i=0;i==4;i++){ sum = sum + Arr[i]; }
	
	LDY #0
	LDA Arr,Y
NEXT	INY
	ADC Arr,Y 
	CPY #4
	BEQ STORE
	JMP NEXT
STORE
	STA Sum
	RTS

CellA	.byte $12
CellB	.byte $8
CellC	.byte $7
Arr	.byte 1,2,3,4,5
Sum	.byte $AA