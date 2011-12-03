;;
;;; It's time to kick ass and chew bubble gum... and I'm all outta gum.
;;;
;;; hw-with-wordcount.asm
;;; SYS 49152
;;;
 
*=$c000
CHROUT = $FFD2					; Alias for CHROUT
NULL = $00
TOKEN = $01

	LDY #$00 				; Reset index register Y
	LDX #$00				; Reset index register X
L0
	LDA STRING1,Y				; Load first string (offset Y)
	CMP #NULL				; Check if null byte (0x00)
	BEQ L1					; If so, then bail out
	JSR CHROUT				; Else, Write A to screen
	INY					;
	JMP L0					; Loop back to beginning
L1
	TYA					; Since we want to save the value of Y, load it into A
	TAX					; Save A (Y) to X, it contains the number of chars
	LDY #$00				; We're done with the first loop, reset Y
L2
	LDA STRING2,Y 				; Load second string (offset Y)
	CMP #NULL 				; Check if zero byte
	BEQ END					; If so, bail out
	CMP #TOKEN				; Check if byte "1"
	BEQ PRINTCHAR				; If so, go to PRINTCHAR 
PRINT_REST	
	JSR CHROUT				; Else, write A to screen
	INY 					;
	JMP L2					; Loop back to beginning

STRING1
	.byte "HELLO WORLD",NULL		; Our first string
STRING2
	.byte " HAS ",TOKEN," CHARACTERS",NULL	; Our second string

END
	RTS 					; Return subroutine

PRINTCHAR					; This is our part for printing X to screen
	TXA					; Get X into A
	CMP #$0A				; Is the value >= 10?
	BCS PRINTHEX				; If so, print as HEX
	JMP PRINTDEC				; Else, print as DEC
PRINTDEC
	CLC					; Clear the carry for the addition
	ADC #$30				; Add the offset for decimal numbers
	JSR CHROUT				; Write the number to screen
	LDA STRING2,Y				; Get the original value of A back
	JMP PRINT_REST
PRINTHEX
	CLC
	ADC #$37
	JSR CHROUT
	LDA STRING2,Y
	JMP PRINT_REST
