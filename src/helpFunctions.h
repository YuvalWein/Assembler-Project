#ifndef MMN14_HELPFUNCTIONS_H
#define MMN14_HELPFUNCTIONS_H

#include <ctype.h>
#include "globalDefines.h"
#include "string.h"

void clean_new_line(char input[],int length);
void remove_blanks(char input[]);
void fill_blank(char input[],int size);
void clean_string(char input[],int size);
void clear_number_array(short input[],int size);
int is_white_char(char input[]);
int is_string_number(char string[]);
#endif
