/*
  decode.h previous operations.h
  bho1 2006
  GPL
*/

#include <stdlib.h>

struct cpu_operator {
  char *name;
  int opcode;
  //  char *adrmode;
  void (* const opfunction)();  //const pointer to operator function
  char *info;
  char *flagsettings;
};


struct cpu_operator operations[];
size_t operations_array_size;



void print_op(struct cpu_operator*);

/*
cdecl> explain void (*lookup_operation(int))();
declare lookup_operation as function (int) returning pointer to function returning void
*/
void (*lookup_operation(int op_code))();

struct cpu_operator* operation_lookup(int op_code);

