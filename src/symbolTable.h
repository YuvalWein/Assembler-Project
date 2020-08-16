#ifndef MMN14_SYMBOLTABLE_H
#define MMN14_SYMBOLTABLE_H

#include "globalDefines.h"
#include <stdlib.h>
#include <string.h>

struct node
{
    int address;
    int external_entry;
    int data_code;
    struct node *next;
    char * label;
};
void add_node(struct node **base,char label[],int address);
struct node * search_by_label(struct node * base,char label[]);
int add_label(struct node **base,char label[],int *address);
void set_data_code(struct node * base,char label[],int data_or_code);
void set_external_entry(struct node * base,char label[],int external_or_entry);
void freeList(struct node **base);
#endif
