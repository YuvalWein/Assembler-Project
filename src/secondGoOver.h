#ifndef MMN14_SECONDGOOVER_H
#define MMN14_SECONDGOOVER_H
#include <stdio.h>
#include <stdlib.h>

#include "helpFunctions.h"
#include "globalDefines.h"
#include "extract.h"
#include "insertToDataTable.h"
#include "symbolTable.h"
#include "handleCommand.h"
#include "handleErrors.h"

int second_go_over(int *IC,int *DC,short srcArray[],short dataArray[],struct node **symbol_table,char file_name[]);
void loop_file_second_time(int *IC,int *DC,short srcArray[],short dataArray[],struct node **symbol_table,FILE *fp);
void cpy_data_to_src(const int *IC,const int *DC,short srcArray[],short dataArray[]);
int handle_entry(struct node **symbol_table,char line[]);
int is_data_string_extern(char data[]);
#endif
