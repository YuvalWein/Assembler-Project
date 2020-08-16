#include "createFiles.h"

/*create the 3 files*/
void create_files(int *IC,int *DC,struct node **symbol_table,short srcArray[],char file_name[])
{
    create_ent_file(symbol_table,file_name);
    create_ext_file(symbol_table,file_name);
    create_ob_file(IC,DC,srcArray,file_name);
}
/*create the ob file*/
void create_ob_file(const int *IC,const int *DC,short srcArray[],char file_name[])
{
    FILE *fp;
    int i;
    char * new_fn=(char *) malloc(strlen(file_name)+FORMAT_AS_LEN);
    strcpy(new_fn,file_name);
    strcat(new_fn,".ob");
    fp = fopen(new_fn, "w+");

    fprintf(fp,"%4d %d\n",*IC,*DC);
    for(i=0;i<(*IC)+(*DC);i++)
    {
        fprintf(fp, "%04d ", (i + BASE_ADDRESS));
        if(srcArray[i]<ZERO)
            fprintf_negative_octal(fp, srcArray[i],5);
        else
            fprintf(fp, "%05o", srcArray[i]);
        fprintf(fp, "\n");
    }
    fclose(fp);
    free(new_fn);
}
/*fpirntf is unable to print negative octal number- this function prints then*/
void fprintf_negative_octal(FILE * fp,short num,int count)
{
    short mask=OCTAL_MASK; /*value of 111 in binary*/
    if(count == BASE)
        return;
    else
        fprintf_negative_octal(fp,(short)(num >> THREE_BITS),(count-ONE));

    fprintf(fp,"%d",num & mask);
}
void create_ent_file(struct node **symbol_table,char file_name[])
{
    create_new_file(symbol_table,file_name,ENTRY);
}
void create_ext_file(struct node **symbol_table,char file_name[])
{
    create_new_file(symbol_table,file_name,EXTERNAL);
}
/*create new ext/ent*/
void create_new_file(struct node **symbol_table,char file_name[], int entry_extern)
{
    FILE *fp;
    char * new_fn=(char *) malloc(strlen(file_name)+FORMAT_LEN);
    strcpy(new_fn,file_name);

    if(entry_extern==ENTRY)
        strcat(new_fn,".ent");
    else
        strcat(new_fn,".ext");

    if(is_ext_ent_exists(*symbol_table,entry_extern))
    {
        fp = fopen(new_fn, "w+");
        write_to_file(*symbol_table, entry_extern, fp);
        fclose(fp);
    }
    free(new_fn);
}
/*write to file ext or ent*/
void write_to_file(struct node *symbol_table,int entry_extern,FILE * fp)
{
    struct node* temp;
    temp=symbol_table;
    while(temp!=NULL)
    {
        if(temp->external_entry==entry_extern)
            if(temp->address!=ZERO)
                fprintf(fp,"%s %04d\n",temp->label,temp->address);
        temp=temp->next;
    }
}
/*check if a node in symbol list is extern/ entry(depends on parameter)*/
int is_ext_ent_exists(struct node *symbol_table,int entry_extern)
{
    struct node* temp;
    temp=symbol_table;
    while(temp!=NULL)
    {
       if(temp->external_entry==entry_extern)
           return TRUE;
        temp=temp->next;
    }
    return FALSE;
}