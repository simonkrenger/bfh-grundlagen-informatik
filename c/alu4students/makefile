# makefile for emu-project - 2005/BHO1

# 2010/BHO1: printing
# 7.2011/BHO1: sdl-card renamed to vc
# revamp: 
# TODO: some makeup, cleaning and, HEY, real doc strings!!

#name of alu main test program
alu_main=alu-main

#name of cpu executable
cpu_exec=cpu

#name of PC executable
pc_exec=pc

IDIR =src/include

LIBS=-lncurses -lm

CC=gcc
#CFLAGS=-g -W -Wall -ansi -pedantic -I$(IDIR)
CFLAGS=-g -W -Wall -I$(IDIR)

VPATH = src/alu:src/util:src/cpu:src/memory:src/test:src/include:src/monitor:src/graphic:src/cpu/c64

# printing: how many colums per source code page
COLS=2


alu-main: alu-main.c register.o alu.o flags.o 
	@echo -e "\ncompiling alu-main"
	$(CC) $(CFLAGS) -o $(alu_main) $^

register.o : register.c register.h
	echo -e "\ncompiling register.o"
	$(CC) $(CFLAGS) -c $<

alu.o : alu.c alu.h alu-opcodes.h register.h flags.o
	@echo -e "\ncompiling alu.o"
	$(CC) $(CFLAGS) -Wno-unused-parameter -c src/alu/alu.c

alu-test: alu-main
	@echo -e "\nrunning alu-test"	
	cat src/test/alu-test.txt | ./$(alu_main)  | diff - src/test/alu-test-results.txt


memory.o : memory.c memory.h
	@echo -e "\ncompiling memory.o"	
	$(CC) $(CFLAGS) -c $<

mem-test: memory.o register.o memory-test.c
	$(CC) $(CFLAGS) -o memory-test src/memory/memory-test.c memory.o register.o
#	cat memory.dump | cpp -nostdinc | sed -e '1,4d' | ./memory-test

decode.o : decode.c decode.h
	@echo -e "\ncompiling decode.o"
	$(CC) $(CFLAGS) -c $<

flags.o : flags.c flags.h
	@echo -e "\ncompiling flags.o"
	$(CC) $(CFLAGS) -c $<

mu-code.o : mu-code.c mu-code.h flags.h
	@echo -e "\ncompiling mu-code.o"
	$(CC) $(CFLAGS) -c $<

cpu-util.o : cpu-util.c cpu-util.h
	@echo -e "\ncompiling cpu-util.o"
	$(CC) $(CFLAGS) -c $<

cpu.o : cpu.c register.h alu.o decode.h alu-opcodes.h cpu-util.h cpu.h monitor.h flags.c
	@echo -e "\ncompiling cpu.o"
	$(CC) $(CFLAGS) -c $<

cpu : cpu.o cpu-util.o decode.o flags.o mu-code.o alu.o register.o memory.o monitor.o 
	@echo -e "\ncompiling cpu.o"
	$(CC) $(CFLAGS) $(LIBS) -o $(cpu_exec) cpu.o memory.o cpu-util.o alu.o register.o decode.o mu-code.o monitor.o 

cpu-main : cpu-main.c cpu.o cpu-util.o mu-code.o decode.o memory.o register.o alu.o decode.o cpu-util.o flags.o 
	@echo -e "\ncompiling cpu-main"
	$(CC) $(CFLAGS) $(LIBS) -o cpu-main $^ 
# cpu.o cpu-util.o mu-code.o decode.o memory.o register.o alu.o

monitor.o : monitor.c cpu.h monitor.h 
	$(CC) $(CFLAGS) -c $<

vc.o : vc.c display.h chardotmatrix.h
	$(CC) $(CFLAGS) -c $< `sdl-config --cflags --libs`

vc-main : vc-main.c vc.o
	$(CC) $(CFLAGS)  `sdl-config --cflags --libs` -o vc-main src/graphic/vc-main.c vc.o


cpu-test : cpu.o cpu-util.o decode.o mu-code.o alu.o register.o memory.o monitor.o
	cat test.dump2 | cpp -nostdinc | sed -e '1,4d' >dump.txt && ./cpu.exe --memory dump.txt

pc : vc.o cpu.o cpu-util.o decode.o mu-code.o alu.o register.o memory.o monitor.o 
	$(CC) $(CFLAGS) $(LIBS) -o $(pc_exec) cpu.o memory.o cpu-util.o alu.o register.o decode.o mu-code.o monitor.o vc.o `sdl-config --cflags --libs`



print : 
	enscript -$(COLS) -j -C -Ec --landscape src/*/*.[ch]

print-alu : 
	enscript -$(COLS) -j -C -Ec --landscape src/alu/alu.c

print-all :
	for i in $(ls */*/*.[hc]); do 
		a2ps --line-numbers=1 -2 -Ec -g -M a4 -o `basename $i`.ps $i; 
	done;

# attention: crap-m$ doesn't do postscript
#for i in $(find . -name "*.c" -print); do enscript -2 -j -Ec --landscape -p - $i | ps2pdf - tmp/`basename $i`.pdf; done 


# for i in $(ls src/cpu/*.c); do a2ps --line-numbers=1 -2 -Ec -g -M a4 -o - $i | ps2pdf -sPAPERSIZE=a4 - `basename $i`.pdf; done
# real printing : M$ doesn't like ps--- fuck them
# a2ps --line-numbers=1 -2 -Ec -g --medium=a4 -o - src/cpu/cpu.c | ps2pdf -sPAPERSIZE=a4 cpu.ps 
# this is not working .. why?? do not know
#print-for-student :
#	for i in $(ls src/cpu/*.c ); do
#		a2ps -g -Ec --line-numbers=1 $i -o `basename $i .c`.ps
# do some ps2pdf for M$ 
#	done;

.PHONY : clean
clean :
	-find . -name "*.o" -exec rm {} \; -print 2>/dev/null
	-rm $(alu_main) 2>/dev/null
	-rm $(cpu_exec) 
	-rm core 
