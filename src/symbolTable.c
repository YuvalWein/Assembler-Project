#include "symbolTable.h"

/*add label to linked list-sign table*/
int add_label(struct node **base,char label[],int *address)
{
    if(search_by_label(*base,label)==NULL)
    {
        add_node(base,label,*address);
        return TRUE;
    }
    return FALSE;
}
/*add new node to a linked list*/
void add_node(struct node **base,char label[],int address)
{
    /*create new node*/
    struct node *newItem;

    newItem = (struct node*) malloc(sizeof(struct node));
    newItem->address=address;
    newItem->data_code=NONE;
    newItem->external_entry=NONE;
    newItem->label=(char *)malloc(strlen(label)+ONE); /*one for \0 char*/

    strcpy(newItem->label,label);

    /*insert to linked list*/
    newItem->next=*base;
    *base=newItem;
}
/*return null if the label doesn't exists in linked list base*/
struct node * search_by_label(struct node * base,char label[])
{
    struct node* temp;
    temp=base;
    while(temp!=NULL)
    {
        if (strcmp(temp->label, label) == IDENTICAL)
            return temp;
        temp=temp->next;
    }
    return NULL;
}
/*set node to be with external/entry flag*/
void set_external_entry(struct node * base,char label[],int external_or_entry)
{
    struct node* temp;
    temp=search_by_label(base,label);
    if(temp==NULL)
        return;
    temp->external_entry=external_or_entry;
}
/*set node to be with data/code flag*/
void set_data_code(struct node * base,char label[],int data_or_code)
{
    struct node* temp;
    temp=search_by_label(base,label);
    if(temp==NULL)
        return;
    temp->data_code=data_or_code;
}
/*free memory for all nodes in list*/
void freeList(struct node **base)
{
    struct node* next=NULL;
    struct node* current_pointer=*base;
    while (current_pointer != NULL)
    {
        next=current_pointer->next;
        free(current_pointer->label);
        free(current_pointer);
        current_pointer=next;
    }
}