; Dieses Programm wartet bis die Taste "S" gedrückt wurde.
; Programmstart mit SYS 49152

*=$c000                  ; Startadresse des Programmes

PRA  =  $dc00            ; CIA#1 (Port Register A)
DDRA =  $dc02            ; CIA#1 (Data Direction Register A)

PRB  =  $dc01            ; CIA#1 (Port Register B)
DDRB =  $dc03            ; CIA#1 (Data Direction Register B)


start    sei             ; Interrupts sperren

         lda #%11111111  ; CIA#1 Port A = Ausgänge 
         sta DDRA             

         lda #%00000000  ; CIA#1 Port B = Eingänge
         sta DDRB             

         lda #%11111101  ; Spalte 1 (COL1) der Matrix testen
         sta PRA
            
loop     lda PRB
         and #%00100000  ; Reihe 5 (ROW5) ausmaskieren
         bne loop        ; Warte bis "S" gedrückt

         cli             ; Interrupts zulassen

ende     rts             ; Rücksprung ins Basic
