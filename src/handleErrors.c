
#include "handleErrors.h"

/*print error by error code, to potential command error */
void print_command_errors(int err_code,int line_number)
{
    switch(err_code)
    {
        case WRONG_OPERANDS:
            printf("ERROR: Wrong operands in command, line: %i \n", line_number);
            break;
        case UNKNOWN_OPERAND_TYPE:
            printf("ERROR: Unknown operand type in command, line: %i \n", line_number);
            break;
        case ILLEGAL_OPERAND:
            printf("ERROR: Illegal operand type in command, line: %i \n", line_number);
            break;
        case UNKNOWN_LABEL:
            printf("ERROR: Unknown label in command, line: %i \n", line_number);
            break;
    }
}
/*check if right  operand type for 1 operand commands*/
int is_legal_one_operand(char command[],int op_type)
{
    if(strcmp(command,"clr")==IDENTICAL || strcmp(command,"not")==IDENTICAL ||
       strcmp(command,"inc")==IDENTICAL || strcmp(command,"dec")==IDENTICAL ||
       strcmp(command,"red")==IDENTICAL)
        return(op_type==DIRECT || op_type==REGISTER_INDIRECT || op_type==REGISTER_DIRECT);

    if(strcmp(command,"jmp")==IDENTICAL || strcmp(command,"bne")==IDENTICAL ||
       strcmp(command,"jsr")==IDENTICAL)
        return (op_type==DIRECT || op_type==REGISTER_INDIRECT);

    if(strcmp(command,"prn")==IDENTICAL)
        return(op_type==IMMEDIATE || op_type==DIRECT ||
               op_type==REGISTER_INDIRECT || op_type==REGISTER_DIRECT);

    return FALSE;
}
/*check if right source operand type for 2 operand commands*/
int is_legal_source_two_operand(char command[],int op_type)
{
    if(strcmp(command,"mov")==IDENTICAL || strcmp(command,"cmp")==IDENTICAL ||
       strcmp(command,"add")==IDENTICAL || strcmp(command,"sub")==IDENTICAL)
        return(op_type==IMMEDIATE || op_type==DIRECT ||
               op_type==REGISTER_INDIRECT || op_type==REGISTER_DIRECT);

    if(strcmp(command,"lea")==IDENTICAL)
        return (op_type==DIRECT);

    return FALSE;
}
/*check if right destination operand type for 2 operand commands*/
int is_legal_dst_two_operand(char command[],int op_type)
{
    if(strcmp(command,"mov")==IDENTICAL || strcmp(command,"lea")==IDENTICAL ||
       strcmp(command,"add")==IDENTICAL || strcmp(command,"sub")==IDENTICAL)
        return(op_type==DIRECT || op_type==REGISTER_INDIRECT || op_type==REGISTER_DIRECT);

    if(strcmp(command,"cmp")==IDENTICAL)
        return(op_type==IMMEDIATE || op_type==DIRECT ||
               op_type==REGISTER_INDIRECT || op_type==REGISTER_DIRECT);


    return FALSE;
}
/*check if a string is a legal register*/
int is_legal_register(char is_register[])
{
    int i;
    char legal_registers[NUM_OF_REGISTERS][REGISTER_LEN]={"r0","r1","r2","r3","r4","r5","r6","r7"};
    for(i=0;i<NUM_OF_REGISTERS;i++)
        if (strcmp(legal_registers[i], is_register) == IDENTICAL)
            return TRUE;
    return FALSE;
}
void string_error(char label[],int line_number)
{
    printf("ERROR: In string %s, line: %i\n",label,line_number);
}
void label_exists_error(char label[],int line_number)
{
    printf("ERROR: label \"%s\" exists, line: %i\n",label,line_number);
}
int is_legal_label(char label[])
{
    return (!isdigit(label[FIRST]) || strlen(label)>MAX_LABEL_LEN);
}