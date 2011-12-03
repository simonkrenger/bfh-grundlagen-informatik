;;
;;; simple-hello-world.asm
;;; compile with
;;; 64tass simple-hello-world.asm -o simple-hello-world
;;; or
;;; make simple-hello-world
;;; Programmstart mit SYS 49152
;;; 
*=$c000
	LDA #10
	TAX
	LDA #12
	TAY
	JSR $FFF0

	LDA #"H"
	JSR $FFD2
	LDA #"E"
	JSR $FFD2	
	LDA #"L"
	JSR $FFD2
	LDA #"L"
	JSR $FFD2	
	LDA #"O"
	JSR $FFD2
	LDA #" "
	JSR $FFD2	
	LDA #"W"
	JSR $FFD2
	LDA #"O"
	JSR $FFD2	
	LDA #"R"
	JSR $FFD2
	LDA #"L"
	JSR $FFD2	
	LDA #"D"
	JSR $FFD2
	
	RTS 
