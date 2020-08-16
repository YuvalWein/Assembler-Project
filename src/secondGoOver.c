#include "secondGoOver.h"

/*rewrite the source array, loop code at the second time*/
int second_go_over(int *IC,int *DC,short srcArray[],short dataArray[],struct node **symbol_table,char file_name[])
{
    FILE *fp;
    fp = fopen(file_name, "r");
    if(fp==NULL)
    {
        printf("ERROR: can't open file: %s\n",file_name);
        return FALSE;
    }
    else
    {
        (*IC)=0;
        loop_file_second_time(IC,DC,srcArray,dataArray,symbol_table,fp);
        cpy_data_to_src(IC,DC,srcArray,dataArray);
    }
    return TRUE;
}
/*loop file-at the second time*/
void loop_file_second_time(int *IC,int *DC,short srcArray[],short dataArray[],struct node **symbol_table,FILE *fp)
{
    char line[MAX_LINE]={'\0'};
    int line_number=1;/*count line numbers for error handle*/
    while(fgets (line, MAX_LINE, fp)!=NULL)
    {
        char data[MAX_LINE] = {'\0'};
        int index = 0;

        clean_new_line(line,(int)strlen(line)+ONE);

        if(is_comment(line))
        {
            line_number++;
            continue;
        }
        /*ignore label definition*/
        index=extract_label(line,data);
        if(data[FIRST]!='\0')
            fill_blank(line,index+ONE);/*+1 to delete the ':' */

        /*if extern- ignore*/
        clean_string(data,(int)strlen(data));
        index=extract_directive(line,data);
        if(is_data_string_extern(data))
        {
            line_number++;
            continue;
        }
        /*add entry*/
        if(strcmp(data,"entry")==IDENTICAL)
        {
            fill_blank(line,index);
            handle_entry(symbol_table,line);
            line_number++;
            continue;
        }
        /*handle command*/
        clean_string(data,(int)strlen(data));
        index=extract_command(line,data);
        if(is_command(data))
        {
            fill_blank(line,index);
            if(handle_command(IC,srcArray,symbol_table,line,data,SECOND)==UNKNOWN_LABEL)
                print_command_errors(UNKNOWN_LABEL,line_number);
        }
        clean_string(data,(int)strlen(data));
        clean_string(line,(int)strlen(line));

        line_number++;
    }
}
/*add entry to the symbol table*/
int handle_entry(struct node **symbol_table,char line[])
{
    char labels[MAX_OPERANDS][MAX_OPERAND_LENGTH]={'\0'};
    int i=0;
    extract_operands(line,labels);
    while (labels[i][FIRST]!='\0')
    {
        struct node * temp=search_by_label(*symbol_table,labels[i]);
        if(temp==NULL)
            return FALSE;
        temp->external_entry=ENTRY;
        i++;
    }
    return TRUE;
}
/*copy data array to the source array*/
void cpy_data_to_src(const int *IC,const int *DC,short srcArray[],short dataArray[])
{
    int place=(*IC);
    int count=0;
    for(;count<(*DC);count++)
    {
        srcArray[place]=dataArray[count];
        place++;
    }
}
/*return if directive is data/extern/string*/
int is_data_string_extern(char data[])
{
    return strcmp(data,"extern")==IDENTICAL || strcmp(data,"string")==IDENTICAL ||
           strcmp(data,"data")==IDENTICAL;
}
