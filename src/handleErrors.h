
#ifndef MMN14_HANDLEERRORS_H
#define MMN14_HANDLEERRORS_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "globalDefines.h"

void print_command_errors(int err_code,int line_number);
int is_legal_one_operand(char command[],int op_type);
int is_legal_register(char is_register[]);
int is_legal_source_two_operand(char command[],int op_type);
int is_legal_dst_two_operand(char command[],int op_type);
int is_legal_label(char label[]);
void label_exists_error(char label[],int line_number);
void string_error(char label[],int line_number);
enum{SUCCESS, WRONG_OPERANDS,UNKNOWN_OPERAND_TYPE,ILLEGAL_OPERAND,UNKNOWN_LABEL,LABEL_EXISTS,STRING_ERROR};
#endif
