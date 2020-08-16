#include "handleCommand.h"

/*handle command on go over 1, and go over 2*/
int handle_command(int *IC,short srcArray[],struct node **symbol_table,char line[],
                   char command[],int go_over_num)
{
    char operands[MAX_OPERANDS][MAX_OPERAND_LENGTH]={'\0'};
    extract_operands(line,operands);

    if(is_zero_operands(command))
    {
        if (operands[FIRST][FIRST] == '\0')
            return handle_zero_operands(IC, srcArray, command);
        else
            return WRONG_OPERANDS;
    }
    if(is_one_operands(command))
    {
        if (!is_white_char(operands[SECOND]))
            return WRONG_OPERANDS;
        else
            return handle_one_operand(IC, srcArray, symbol_table, command, operands[FIRST], go_over_num);
    }
    if(is_two_operands(command))
        return handle_two_operands(IC,srcArray,symbol_table,command,operands,go_over_num);

    return NO_COMMAND;
}
/*in case of 2 operand command*/
int handle_two_operands(int *IC,short srcArray[],struct node **symbol_table,
                        char command[],char operands[MAX_OPERANDS][MAX_OPERAND_LENGTH],int go_over_num)
{
    int source_operand=REGISTER_DIRECT,dest_operand=REGISTER_DIRECT;/*default values*/
    int op_code;
    int insert_source,insert_dst;

    if(!set_operand_type(operands[FIRST],&source_operand) ||
       !set_operand_type(operands[SECOND],&dest_operand))
        return UNKNOWN_OPERAND_TYPE;

    if(!is_legal_source_two_operand(command,source_operand) || !is_legal_dst_two_operand(command,dest_operand))
        return ILLEGAL_OPERAND;

    op_code=get_op_code(command);
    insert_command(IC,srcArray,op_code,dest_operand,source_operand);
    /*both register--> one line in memory*/
    if(is_both_register(source_operand,dest_operand))
    {
        insert_operand_double_register(IC,srcArray,operands[FIRST][SECOND] - '0',
                                       operands[SECOND][SECOND] - '0');
        return SUCCESS;
    }

    insert_source= set_operand_in_memory(IC,srcArray,symbol_table,source_operand,
                                        operands[FIRST],SOURCE,go_over_num);
    insert_dst= set_operand_in_memory(IC,srcArray,symbol_table,dest_operand,
                                         operands[SECOND],DESTINATION,go_over_num);
    if(insert_source==SUCCESS)
        return insert_dst;
    return insert_source;
}
/*for one operand commands*/
int handle_one_operand(int *IC,short srcArray[],struct node **symbol_table,char command[],char operand[],int go_over_num)
{
    int dest_operand=REGISTER_DIRECT;
    int op_code;
    
    if(!set_operand_type(operand,&dest_operand))
        return UNKNOWN_OPERAND_TYPE;
    if(!is_legal_one_operand(command,dest_operand))
        return ILLEGAL_OPERAND;

    op_code=get_op_code(command);
    insert_command(IC,srcArray,op_code,dest_operand,NO_OPERAND);

    return set_operand_in_memory(IC,srcArray,symbol_table,dest_operand,operand,
                          DESTINATION,go_over_num);
}
/*for zero operands commands*/
int handle_zero_operands(int *IC,short srcArray[],char command[])
{
    int i;
    struct command_list cmd_lst[NUM_OF_ZERO_OPERANDS]={{RST,"rst"},
                                                       {STOP,"stop"}};

    for (i = 0; i <NUM_OF_ZERO_OPERANDS ; i++)
        if(strcmp(command,cmd_lst[i].op_name)==IDENTICAL)
        {
            insert_command(IC, srcArray, cmd_lst[i].op_code, NO_OPERAND, NO_OPERAND);
            return SUCCESS;
        }
    return NO_COMMAND;
}
/*insert operand to source memory*/
int set_operand_in_memory(int *IC,short srcArray[],struct node **symbol_table,int operand,char operand_val[],
                           int source_or_dst,int go_over_num)
{
    int place=source_or_dst==SOURCE?SOURCE_OP_PLACE_REGISTER:DEST_OP_PLACE;
    if(operand==REGISTER_DIRECT || operand==REGISTER_INDIRECT)
        insert_operand_register(IC,srcArray,operand_val[SECOND]-'0',place);
    else if(operand==DIRECT)
    {
        struct node * dst_op_node=search_by_label(*symbol_table,operand_val);
        /*check for errors in second go over*/
        if(go_over_num==SECOND)
        {
            /*return error in no label*/
            if(dst_op_node==NULL)
                return UNKNOWN_LABEL;
            else
            {
                int a_r_e;
                /*add external node to symbol list with line number-for ext file*/
                if(dst_op_node->external_entry==EXTERNAL)
                {
                    add_node(symbol_table, operand_val, (*IC)+BASE_ADDRESS);
                    set_external_entry(*symbol_table, operand_val, EXTERNAL);
                }
                a_r_e=(dst_op_node->external_entry==EXTERNAL)?E_POSITION:R_POSITION;
                insert_operand_direct(IC,srcArray,ONE,a_r_e);
            }
        } else
            insert_operand_direct(IC,srcArray,NONE,A_POSITION);/*first go over*/
    }
    else if(operand==IMMEDIATE)
    {
        if(!is_string_number(operand_val))
            return ILLEGAL_OPERAND;

        insert_operand_immediate(IC, srcArray, atoi(operand_val));
    }else
            return ILLEGAL_OPERAND;

    return SUCCESS;
}
/*check if the 2 operands are register*/
int is_both_register(int source_operand,int dest_operand)
{
    return (source_operand==REGISTER_DIRECT && dest_operand==REGISTER_DIRECT)   ||
           (source_operand==REGISTER_DIRECT && dest_operand==REGISTER_INDIRECT) ||
           (source_operand==REGISTER_INDIRECT && dest_operand==REGISTER_DIRECT) ||
           (source_operand==REGISTER_INDIRECT && dest_operand==REGISTER_INDIRECT);
}
/*found the operand type(direct, immediate...)*/
int set_operand_type(char operand[],int * operand_type)
{
    remove_blanks(operand);

    if(is_immediate(operand,operand_type))
        return TRUE;

    is_register_indirect(operand,operand_type);
    if(is_legal_register(operand))
        return TRUE;

    if(!isdigit(operand[FIRST]))
    {
        (*operand_type)=DIRECT;
        return TRUE;
    }
    return FALSE;
}
/*check if the register is indirect*/
int is_register_indirect(char operand[],int *operand_type)
{
    if(operand[FIRST]=='*')
    {
        (*operand_type)=REGISTER_INDIRECT;
        operand[FIRST]=' ';
        remove_blanks(operand);
        return TRUE;
    }
    return FALSE;
}
/*check if opernad is immediate*/
int is_immediate(char operand[],int *operand_type)
{
    if(operand[FIRST]=='#')
    {
        (*operand_type) = IMMEDIATE;
        operand[FIRST] = ' ';
        remove_blanks(operand);
        return TRUE;
    }
    return FALSE;
}
/*check if command has 0 operands*/
int is_zero_operands(char command[])
{
    return (strcmp(command,"rts")==IDENTICAL || strcmp(command,"stop")==IDENTICAL);
}
/*check if command has 1 operands*/
int is_one_operands(char command[])
{
    return (strcmp(command,"clr")==IDENTICAL || strcmp(command,"not")==IDENTICAL ||
            strcmp(command,"inc")==IDENTICAL || strcmp(command,"dec")==IDENTICAL ||
            strcmp(command,"jmp")==IDENTICAL || strcmp(command,"bne")==IDENTICAL ||
            strcmp(command,"red")==IDENTICAL || strcmp(command,"prn")==IDENTICAL ||
            strcmp(command,"jsr")==IDENTICAL);
}
/*check if command has 2 operands*/
int is_two_operands(char command[])
{
    return (strcmp(command,"mov")==IDENTICAL || strcmp(command,"cmp")==IDENTICAL ||
            strcmp(command,"add")==IDENTICAL || strcmp(command,"sub")==IDENTICAL ||
            strcmp(command,"lea")==IDENTICAL);
}
/*get op_code for every command*/
short get_op_code(char command[])
{
    int i;
    struct command_list cmd_lst[NUM_OF_COMMANDS]={
            {MOV,"mov"},{CMP,"cmp"},{ADD,"add"},
            {SUB,"sub"},{LEA,"lea"},{CLR,"clr"},
            {NOT,"not"},{INC,"inc"},{DEC,"dec"},
            {JMP,"jmp"},{BNE,"bne"},{RED,"red"},
            {PRN,"prn"},{JSR,"jsr"},{RST,"rst"},
            {STOP,"stop"}
    };
    for(i=0;i<NUM_OF_COMMANDS;i++)
        if(strcmp(cmd_lst[i].op_name,command)==IDENTICAL)
            return cmd_lst[i].op_code;

    return NO_COMMAND;
}
/*check if a string is a command*/
int is_command(char command[])
{
    return (is_two_operands(command) || is_one_operands(command) || is_zero_operands(command));
}

