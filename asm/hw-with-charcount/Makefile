# Kick-ass makefile for ASM, 64tass and the x64 emulator
# Simon Krenger, 2011-11-15

AC = 64tass
ASM = $(wildcard *.asm)
OBJ = $(ASM:%.asm=%.prg)
EMU = x64

all: emulate

emulate: $(OBJ)
	$(EMU) $(OBJ)

%.prg: %.asm
	if $(AC) $< -o $(OBJ) ; then \
		echo "Compiler OK"; \
	else \
		echo "Compiler returned 1"; exit 1; fi
