#include "insertToDataTable.h"
/*insert string to the data array*/
void insert_string(int *DC,short int dataArray[SRC_ARRAY_SIZE],char string[])
{
    int i;
    for(i=0;i<strlen(string)+ONE;i++) /*+1 for \0 at the end*/
    {
        dataArray[*DC]=string[i];
        (*DC)++;
    }
}
/*insert number to the data array*/
void insert_number(int *DC,short int dataArray[SRC_ARRAY_SIZE],short number)
{
    dataArray[*DC]=number;
    (*DC)++;
}