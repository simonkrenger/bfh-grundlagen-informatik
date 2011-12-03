;; Histogram exercise
*=$c000

;; Define some aliases
CHROUT = $FFD2
NULL = $00

	LDX #$00		; Reset index register X
MAINLOOP			;; Outer loop for the array
	LDA histogram,X		; Load number of hash signs into A
	CMP #NULL		; Are we at the end of the array?
	BEQ ENDPROG		; If so, finish the program
	JSR PRINTVAL		; Else, print the value in A
	INX			; After printing, increment X
	JMP MAINLOOP		; Loop back to the outer loop

PRINTVAL			; This subroutine is for printing n hash signs
	LDY #$00		; Reset Y
	STA temp		; Store A to TEMP
HASHLOOP			;; Inner loop for printing hash signs
	TYA			; Get Y into A
	CMP temp		; Check if we need to print more chars
	BEQ ENDHASHLOOP		; If not, end the subroutine
	JSR PRINTHASH		; Else, print one hash sign
	INY			; Increment Y
	JMP HASHLOOP		; Loop back
ENDHASHLOOP
	LDA #$0D		; Load CR into A
	JSR CHROUT		; Print CR
	LDA temp		; Get A back from temp
	RTS			; Return from subroutine

PRINTHASH			; Print one hash sign
	PHA			; Push A into stack
	LDA #$23		; Load hash into A
	JSR CHROUT		; Print hash sign
	PLA			; Pull A from stack
	RTS			; Return

ENDPROG
	RTS

temp
	.byte $00
histogram
	.byte 5,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,16,15,14,13,12,NULL
