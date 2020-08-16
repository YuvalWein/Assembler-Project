
#include "insertToSrc.h"
/*insert to the main array the command line of memory*/
void insert_command(int *IC,short int srcArray[SRC_ARRAY_SIZE],int op_code,int dst_operand,int source_operand)
{
    mask_code(IC,srcArray,ONE,A_POSITION);
    mask_code(IC,srcArray,op_code,OP_CODE_PLACE);
    if(dst_operand != NO_OPERAND)
        mask_code(IC,srcArray,ONE,dst_operand+DEST_OP_PLACE);
    if(source_operand != NO_OPERAND)
        mask_code(IC,srcArray,ONE,source_operand+SOURCE_OP_PLACE_COMMAND);
    (*IC)+=ONE;
}
/*mask data inside main source memory*/
void mask_code(int *IC,short srcArray[SRC_ARRAY_SIZE],int code,int place)
{
    short mask= (short) code;
    mask<<=place;
    srcArray[(*IC)] |= mask;
}
/*insert number to the source array*/
void insert_operand_immediate(int *IC,short srcArray[SRC_ARRAY_SIZE],int operand_value)
{
    mask_code(IC,srcArray,ONE,A_POSITION);
    mask_code(IC,srcArray,operand_value,DEST_OP_PLACE);
    (*IC)+=ONE;
}
/*insert label address to source array*/
void insert_operand_direct(int *IC,short srcArray[SRC_ARRAY_SIZE],int operand_value,int A_R_E)
{
    mask_code(IC,srcArray,ONE,A_R_E);
    mask_code(IC,srcArray,operand_value,DEST_OP_PLACE);
    (*IC)+=ONE;
}
/*insert register to source array*/
void insert_operand_register(int *IC,short srcArray[SRC_ARRAY_SIZE],int operand,
                             int dest_or_source)
{
    mask_code(IC,srcArray,ONE,A_POSITION);
    mask_code(IC,srcArray,operand,dest_or_source);
    (*IC)+=ONE;
}
/*insert 2 register in one line of memory in source array*/
void insert_operand_double_register(int *IC,short srcArray[SRC_ARRAY_SIZE],
                                     int source_val,int dst_val)
{
    mask_code(IC,srcArray,ONE,A_POSITION);
    mask_code(IC,srcArray,source_val,SOURCE_OP_PLACE_REGISTER);
    mask_code(IC,srcArray,dst_val,DEST_OP_PLACE);
    (*IC)+=ONE;
}


