#include "extract.h"

/*extract the command from the line and enter it to command string*/
int extract_command(const char line[],char command[])
{
    int start=getIndexOfFirstNonBlank(line);

    int i=0;
    while(line[i+start]!='\0' && line[i+start]!=' ' && line[i+start]!='\t' && i<MAX_COMMAND_LENGTH)
    {
        command[i]=line[i+start];
        i++;
    }
    return i+start;
}
/*return if line is a comment*/
int is_comment(const char line[])
{
    int start=getIndexOfFirstNonBlank(line);
    return (line[start]==';');
}
/*extract the operand from the line*/
void extract_operands(const char line[],char operands[MAX_OPERANDS][MAX_OPERAND_LENGTH])
{
    char input[MAX_LINE];
    char *token;
    int i=0;

    strcpy(input,line);
    remove_blanks(input);
    token=strtok(input,",");

    while(token != NULL)
    {
        if(i>MAX_OPERANDS)
        {
            operands[FIRST][FIRST]='\0';
            break;
        }
        strcpy(operands[i],token);
        token=strtok(NULL, ",");
        i++;
    }
}
/*get label if exists, from line of code*/
int extract_label(const char line[],char label[])
{
    int start=getIndexOfFirstNonBlank(line);
    int i=0;
    while(i < MAX_LINE && line[i + start] != '\0' && line[i + start] != ' ' && line[i + start] != '\t')
    {
        if(line[i+start]== ':')
            return i+start;

        label[i]=line[i+start];
        i++;
    }
    clean_string(label,i);/*no label-clean string*/
    return FALSE;
}
/*extract directive(extern..) from line*/
int extract_directive(const char line[],char directive[])
{
    int start=getIndexOfFirstNonBlank(line);
    int i=0;
    if(line[start]!='.')
        return i;
    start++;
    while(i < MAX_LINE && line[i + start] != '\0' && line[i + start] != ' ' && line[i + start] != '\t')
    {
        directive[i]=line[i+start];
        i++;
    }
    return start+i;
}
/*extract string from line of code*/
int extract_string(const char line[],char string[])
{
    int start=getIndexOfFirstNonBlank(line);
    int i=0;
    if(line[start]!='\"')
        return i;
    start++;
    while(line[i + start]!='\"' && i < MAX_LINE && line[i + start] != '\0')
    {
        string[i]=line[i+start];
        i++;
    }
    if(line[start+i]!='\"')
    {
        clean_string(string,MAX_LINE);
        return FALSE;
    }
    return start+i;
}
/*extract data directive from line of code*/
int extract_data(const char line[],short data[MAX_LINE])
{
    char input[MAX_LINE];
    char *token;
    int i=0;

    strcpy(input,line);
    token=strtok(input,",");
    while(token != NULL)
    {
        data[i]=atoi(token);
        token=strtok(NULL, ",");
        i++;
    }
    return i;
}
/*return the index of the first char that is not white char from the input string*/
int getIndexOfFirstNonBlank(const char input[])
{
    int start=0;
    /*pass blank cells*/
    while(input[start]==' ' || input[start]=='\t')
        start++;
    return start;
}