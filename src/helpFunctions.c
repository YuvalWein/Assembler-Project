

#include "helpFunctions.h"
/*delete all new lines in the string input*/
void clean_new_line(char input[],int length)
{
    int i=0;
    for(i=0;i<length;i++)
        if(input[i]=='\n')
            input[i]='\0';
}
/*remove all white characters from input array including new line*/
void remove_blanks(char input[])
{
    int buffIndex=0,i=0;
    char buffer[MAX_LINE];
    for(i=0;i<MAX_LINE;i++)
    {
        if (input[i] != ' ' && input[i] != '\t' && input[i] != '\n')
        {
            buffer[buffIndex]=input[i];
            buffIndex++;
        }
    }
    strcpy(input,buffer);
}
/*fill input in blanks until "size" position*/
void fill_blank(char input[],int size)
{
    int i=0;
    for(;i<size;i++)
        input[i]=' ';
}
/*set cells as blank from 'size' cells in array input*/
void clean_string(char input[],int size)
{
    int i=0;
    for(;i<size;i++)
        input[i]='\0';
}
/*check if input has white char inside*/
int is_white_char(char input[])
{
    int i=0;
    for(i=0;i<strlen(input);i++)
        if(input[i]!=' ' && input[i]!='\t' && input[i]!='\0' && input[i]!='\n')
            return FALSE;
    return TRUE;
}
/*check if string has only numbers/+/- */
int is_string_number(char string[])
{
    int i;
    for(i=0; i<strlen(string);i++)
        if(!isdigit(string[i]) && string[i]!='+' && string[i]!='-')
            return FALSE;
    return TRUE;
}
/*set all cells in input array to zero*/
void clear_number_array(short input[],int size)
{
    int i=0;
    for(;i<size;i++)
        input[i]=0;
}