
#ifndef MMN14_INSERTTOSRC_H
#define MMN14_INSERTTOSRC_H
#include <stdio.h>
#include "globalDefines.h"
#include "helpFunctions.h"

#define OP_CODE_PLACE 11
#define SOURCE_OP_PLACE_COMMAND 7


void insert_command(int *IC,short srcArray[SRC_ARRAY_SIZE],int op_code,int dst_operand,int source_operand);
void mask_code(int *IC,short srcArray[SRC_ARRAY_SIZE],int op_code,int place);

void insert_operand_register(int *IC,short srcArray[SRC_ARRAY_SIZE],int operand,int dest_or_source);
void insert_operand_double_register(int *IC,short srcArray[SRC_ARRAY_SIZE],int source_val,int dst_val);
void insert_operand_immediate(int *IC,short srcArray[SRC_ARRAY_SIZE],int operand_value);
void insert_operand_direct(int *IC,short srcArray[SRC_ARRAY_SIZE],int operand_value,int A_R_E);

#endif
