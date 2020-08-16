#ifndef MMN14_CREATEFILES_H
#define MMN14_CREATEFILES_H
#include <stdio.h>
#include <stdlib.h>
#include "symbolTable.h"
#include "globalDefines.h"

#define FORMAT_LEN 4
#define OCTAL_MASK 7
#define THREE_BITS 3
#define BASE 0
void create_files(int *IC,int *DC,struct node **symbol_table,short srcArray[],char file_name[]);
void create_ob_file(const int *IC,const int *DC,short srcArray[],char file_name[]);
void create_new_file(struct node **symbol_table,char file_name[], int entry_extern);
void create_ent_file(struct node **symbol_table,char file_name[]);
void create_ext_file(struct node **symbol_table,char file_name[]);
void write_to_file(struct node *symbol_table,int entry_extern,FILE * fp);
int is_ext_ent_exists(struct node *symbol_table,int entry_extern);
void fprintf_negative_octal(FILE * fp,short num,int count);
#endif