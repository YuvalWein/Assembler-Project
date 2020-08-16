#ifndef MMN14_EXTRACT_H
#define MMN14_EXTRACT_H

#include "globalDefines.h"
#include "helpFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int extract_command(const char line[],char command[]);
int extract_string(const char line[],char string[]);
void extract_operands(const char line[],char operands[MAX_OPERANDS][MAX_OPERAND_LENGTH]);
int extract_label(const char line[],char label[]);
int extract_data(const char line[],short data[MAX_LINE]);
int extract_directive(const char line[],char directive[]);
int getIndexOfFirstNonBlank(const char input[]);
int is_comment(const char line[]);
#endif
