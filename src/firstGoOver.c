

#include "firstGoOver.h"

/*This function will loop all lines in file and set the format of the ob memory, symbol list, and extern*/
int first_go_over(int *IC,int *DC,short srcArray[],short dataArray[],struct node **symbol_table,char file_name[])
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
        loop_file(IC,DC,srcArray,dataArray,symbol_table,fp);
        update_data_label_address(IC,*symbol_table);
        fclose(fp);

        clear_number_array(srcArray,SRC_ARRAY_SIZE);
    }
    return TRUE;
}
/*loop line by line and analyze commands*/
void loop_file(int *IC,int *DC,short srcArray[],short dataArray[],struct node **symbol_table,FILE *fp)
{
    char line[MAX_LINE]={'\0'};
    int line_number=1;
    int is_action=FALSE;/*check if unknown command*/
    while(fgets (line, MAX_LINE, fp)!=NULL)
    {
        char data[MAX_LINE]={'\0'};
        int index=0;

        clean_new_line(line,(int)strlen(line)+ONE);

        if(is_comment(line))
        {
            line_number++;
            continue;
        }

        /*handle data and string WITHOUT label*/
        index=extract_directive(line,data);
        if(strcmp(data,"data")==IDENTICAL)
        {
            fill_blank(line,index);
            handle_data(DC, dataArray, symbol_table, line, NULL);
            is_action=TRUE;
        }
        if(strcmp(data,"string")==IDENTICAL)
        {
            fill_blank(line,index);
            handle_string(DC, dataArray, symbol_table, line, NULL);
            is_action=TRUE;

        }
        /*handle labels*/
        clean_string(data,(int)strlen(data));
        index=extract_label(line,data);
        if(data[FIRST]!='\0')
        {
            fill_blank(line,index+ONE);/*+1 to delete the ':' */
            if(!is_legal_label(data))
            {
                is_action=TRUE;
                printf("ERROR: Illegal label name, line: %i\n",line_number);
            }else
                is_action=handle_label(IC,DC,dataArray,symbol_table,line,data);
            /*error handle in label*/
            if(is_action==LABEL_EXISTS)
                label_exists_error(data,line_number);
            if(is_action==STRING_ERROR)
                string_error(data,line_number);
        }
        /*add extern*/
        clean_string(data,(int)strlen(data));
        index=extract_directive(line,data);
        if(strcmp(data,"extern")==IDENTICAL)
        {
            fill_blank(line,index);
            handle_extern(symbol_table,line);
            is_action=TRUE;
        }
        /*do nothing with entry command-wait to second go*/
        if(strcmp(data,"entry")==IDENTICAL)
            is_action=TRUE;

        /*handle commands*/
        clean_string(data,(int)strlen(data));
        index=extract_command(line,data);
        if(is_command(data))
        {
            fill_blank(line,index);
            print_command_errors(handle_command(IC,srcArray,symbol_table,line,data,FIRST),line_number);
            is_action=TRUE;
        }

        if(!is_action && !is_white_char(line))
            printf("ERROR: Unknown command, line: %i \n",line_number);

        clean_string(data,(int)strlen(data));
        clean_string(line,(int)strlen(line));

        line_number++;
        is_action=FALSE;
    }
}
/*handle externs*/
void handle_extern(struct node **symbol_table,char line[])
{
    int i=0;
    int ext_address=0;
    char operands[MAX_OPERANDS][MAX_OPERAND_LENGTH]={'\0'};
    extract_operands(line,operands);
    while(operands[i][FIRST]!='\0')
    {
        add_label(symbol_table,operands[i],&ext_address);
        set_external_entry(*symbol_table,operands[i],EXTERNAL);
        i++;
    }
}
/*handle labels- string/data/commands*/
int handle_label(const int *IC,int *DC,short dataArray[],struct node **symbol_table,char line[],char label[])
{
    char directive[MAX_LINE]={'\0'};
    int index=extract_directive(line,directive);
    fill_blank(line,index);

    if(strcmp(directive,"string")==IDENTICAL)
        return handle_string(DC, dataArray, symbol_table, line, label);

    if(strcmp(directive,"data")==IDENTICAL)
       return handle_data(DC, dataArray, symbol_table, line, label);

    /*label for command*/
    extract_command(line,directive);
    if(is_command(directive))
    {
        int  address=(*IC)+BASE_ADDRESS;
        if(!add_label(symbol_table,label,&address))
            return LABEL_EXISTS;
        set_data_code(*symbol_table,label,CODE);
        return TRUE;
    }
    return FALSE;
}
/*add data to data Array*/
int handle_data(int *DC,short dataArray[],struct node **symbol_table,char line[],char label[])
{
    short data[MAX_LINE] = {'\0'};
    int i, num_of_numbers;

    if (label != NULL)
    {
        if(!add_label(symbol_table, label, DC))
            return LABEL_EXISTS;/*error-label exists*/
        set_data_code(*symbol_table, label, DATA);
    }

    num_of_numbers = extract_data(line, data);
    for(i=0;i<num_of_numbers;i++)
        insert_number(DC,dataArray,data[i]);

    return TRUE;
}
/*add string to data Array*/
int handle_string(int *DC,short dataArray[],struct node **symbol_table,char line[],char label[])
{
    int index=0;
    char string[MAX_LINE]={'\0'};
    index=extract_string(line,string);
    if(index!=0)
    {
        if (label != NULL)
        {
            if(!add_label(symbol_table, label, DC))
                return LABEL_EXISTS;
            set_data_code(*symbol_table, label, DATA);
        }
        insert_string(DC,dataArray,string);
    } else
        return STRING_ERROR;

    return TRUE;
}
/*add 100 to every data label at the end of first go over*/
void update_data_label_address(const int *IC,struct node *symbol_table)
{
    struct node* temp;
    temp=symbol_table;
    while(temp!=NULL)
    {
        if(temp->data_code==DATA)
            temp->address+=(*IC)+BASE_ADDRESS;
        temp=temp->next;
    }
}
