
#ifndef MMN14_GLOBALDEFINES_H
#define MMN14_GLOBALDEFINES_H

#define SRC_ARRAY_SIZE 100
#define ONE 1
#define TRUE 1
#define FALSE 0
#define FIRST 0
#define SECOND 1
#define NUM_OF_COMMANDS 16
#define MAX_COMMAND_LENGTH 5
#define MAX_OPERANDS 2
#define MAX_OPERAND_LENGTH 100
#define MAX_LINE 81
#define DEST_OP_PLACE 3
#define IDENTICAL 0
#define SOURCE_OP_PLACE_REGISTER 6
#define BASE_ADDRESS 100
#define NO_OPERAND (-1)
#define NO_COMMAND (-1)
#define NUM_OF_ZERO_OPERANDS 2
#define NUM_OF_REGISTERS 8
#define REGISTER_LEN 3
#define MAX_FILE_LEN 30
#define FORMAT_AS_LEN 3
#define MAX_LABEL_LEN 31
#define ZERO 0
enum{IMMEDIATE,DIRECT,REGISTER_INDIRECT,REGISTER_DIRECT};
enum{E_POSITION,R_POSITION,A_POSITION};
enum{NONE,EXTERNAL,ENTRY};
enum{SOURCE,DESTINATION};
enum{NO_DEF,DATA,CODE};
enum {MOV,CMP,ADD,SUB,LEA,CLR,NOT,INC,DEC,JMP,BNE,RED,PRN,JSR,RST,STOP};
struct command_list{
    short int op_code;
    char * op_name;
};
#endif
