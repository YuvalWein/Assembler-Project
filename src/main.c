/*mmn 14 Yuval Weinberger 206821779*/
#include <stdio.h>
#include "globalDefines.h"
#include "symbolTable.h"
#include "insertToDataTable.h"
#include "firstGoOver.h"
#include "secondGoOver.h"
#include "createFiles.h"

#define ERROR 1

/*
 * This function will activate the assembler, loop all files,
 * create ent,ext and ob file,
 * and rise errors if needed.
 */
int main(int argc, char *argv[])
{

    int i;
    /*loop all files*/
    for(i=1;i<argc;i++)
    {
        short int srcArray[SRC_ARRAY_SIZE] = {0};
        short int dataArray[SRC_ARRAY_SIZE] = {0};
        int IC = 0;
        int DC = 0;
        struct node *symbol_table = NULL;

        /*create file name with extension*/
        char *fn = (char *) malloc(strlen(argv[i]) + FORMAT_AS_LEN);
        if(fn==NULL)
        {
            printf("No memory, fatal error, exiting...\n");
            return ERROR;
        }
        strcpy(fn, argv[i]);
        strcat(fn, ".as");

        /*first, second go over and create files*/
        if(first_go_over(&IC, &DC, srcArray, dataArray, &symbol_table, fn)
           && second_go_over(&IC, &DC, srcArray, dataArray, &symbol_table, fn))
            create_files(&IC, &DC, &symbol_table, srcArray, argv[i]);

        /*free symbol table from memory*/
        free(symbol_table);
        free(fn);
    }
    return 0;
}
