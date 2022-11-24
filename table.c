#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "log.c"
FILE *ptr;

int createTable(char *tableName, int numCol, ...);
int deleteTable(char *tableName);

int createTable(char *tableName, int numCol, ...)
{
    va_list arg;
    ptr = fopen(tableName, "r");
    if (ptr == NULL)
    {
        ptr = fopen(tableName, "w");
        va_start(arg, numCol);
        for (int i = 0; i < numCol; i++)
        {
            fprintf(ptr, "%s", va_arg(arg, int));
            if (i + 1 != numCol)
            {
                fprintf(ptr, ",");
            }
        }
        va_end(arg);
        fprintf(ptr, "\n");
        fclose(ptr);
        writeLog(3, "New table created");
        return 1;
    }
    fclose(ptr);
    writeLog(1, "Table already exists");
    return -1;
}
int deleteTable(char *tableName)
{
    if (remove(tableName) == 0)
    {
        writeLog(3, "Table removed successfully");
        return 1;
    }
    writeLog(1, "No such table found");
    return -1;
}
