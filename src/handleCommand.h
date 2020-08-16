#ifndef MMN14_HANDLECOMMAND_H
#define MMN14_HANDLECOMMAND_H

#include <ctype.h>
#include "globalDefines.h"
#include "string.h"
#include "extract.h"
#include "symbolTable.h"
#include "insertToSrc.h"
#include "handleErrors.h"

int is_zero_operands(char command[]);
int is_one_operands(char command[]);
int is_two_operands(char command[]);
int is_command(char command[]);
int handle_command(int *IC,short srcArray[],struct node **symbol_table,char line[],char command[],int go_over_num);
int handle_zero_operands(int *IC,short srcArray[],char command[]);
int handle_two_operands(int *IC,short srcArray[],struct node **symbol_table,char command[],char operands[MAX_OPERANDS][MAX_OPERAND_LENGTH],int go_over_num);
int handle_one_operand(int *IC,short srcArray[],struct node **symbol_table,char command[],char operand[],int go_over_num);
int set_operand_in_memory(int *IC,short srcArray[],struct node **symbol_table,int operand,char operand_val[],
                           int source_or_dst,int go_over_num);
short get_op_code(char command[]);
int is_register_indirect(char operand[],int *operand_type);
int is_immediate(char operand[],int *operand_type);
int set_operand_type(char operand[],int * operand_type);
int is_both_register(int source_operand,int dest_operand);

#endif
