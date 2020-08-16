

#ifndef MMN14_FIRSTGOOVER_H
#define MMN14_FIRSTGOOVER_H
#include <stdio.h>
#include <stdlib.h>

#include "helpFunctions.h"
#include "globalDefines.h"
#include "extract.h"
#include "insertToDataTable.h"
#include "symbolTable.h"
#include "handleCommand.h"
#include "handleErrors.h"

int first_go_over(int *IC,int *DC,short srcArray[],short dataArray[],struct node **symbol_table,char file_name[]);
void loop_file(int *IC,int *DC,short srcArray[],short dataArray[],struct node **symbol_table,FILE *fp);
void update_data_label_address(const int *IC,struct node *symbol_table);
int handle_label(const int *IC,int *DC,short dataArray[],struct node **symbol_table,char line[],char label[]);
int handle_string(int *DC,short dataArray[],struct node **symbol_table,char line[],char label[]);
int handle_data(int *DC,short dataArray[],struct node **symbol_table,char line[],char label[]);
void handle_extern(struct node **symbol_table,char line[]);
#endif
