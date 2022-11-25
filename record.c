#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define DATA_BUFF 10000
int insertRecord(char *tableName, int numArg, ...);
int updateRecord(char *tableName, char *searchFor, char *searchValue, char *updateFor, char *updateValue);
int searchRecord(char *tableName, char *searchFor, char *searchValue);
int deleteRecord(char *tableName, char *searchFor, char *searchValue);
// Helper function
int getSearchIndexValue(char *searchFor, FILE *ptr);
int doesSearchValueMatch(char *searchValue, char *ch, int searchIndex);
void writeCharFile(FILE *ptr, char *data);

int insertRecord(char *tableName, int numArg, ...)
{
    FILE *ptr, *tempPtr, *tempData;
    va_list arg;
    char ch_A[DATA_BUFF], ch_B[DATA_BUFF];
    int count_A, count_B, max_A, max_B, flag = 0, flag_a = 0;

    tempData = fopen("TempData", "w+");
    va_start(arg, numArg);
    for (int i = 0; i < numArg; i++)
    {
        fprintf(tempData, "%s", va_arg(arg, int));
        if (i + 1 < numArg)
            fprintf(tempData, ",");
    }
    fprintf(tempData, "\n");
    va_end(arg);
    rewind(tempData);
    fscanf(tempData, "%[^\n]s", &ch_B);
    fclose(tempData);
    remove("TempData");

    ptr = fopen(tableName, "r+");
    tempPtr = fopen("T", "a+");

    fscanf(ptr, "%[^\n]s", &ch_A);
    fgetc(ptr);
    writeCharFile(tempPtr, ch_A);

    max_B = strlen(ch_B);
    while (fscanf(ptr, "%[^\n]s", &ch_A) != EOF)
    {
        fgetc(ptr);
        if (flag == 1)
        {
            writeCharFile(tempPtr, ch_A);
            continue;
        }
        // Comparision
        max_A = strlen(ch_A);
        count_A = -1;
        count_B = -1;
        while (count_A < max_A && count_B < max_B)
        {
            count_A++;
            count_B++;
            if (count_A == max_A && count_B == max_B)
            {
                writeCharFile(tempPtr, ch_A);
                break;
            }
            if (ch_A[count_A] == ',')
            {
                while (count_B < max_B && ch_B[count_B] != ',')
                    count_B++;
                continue;
            }
            if (ch_B[count_B] == ',')
            {
                while (count_A < max_A && ch_A[count_A] != ',')
                    count_A++;
                continue;
            }
            if (ch_A[count_A] < ch_B[count_B])
            {
                writeCharFile(tempPtr, ch_A);
                break;
            }
            if (ch_B[count_B] == ',' || ch_A[count_A] > ch_B[count_B])
            {
                flag = 1;
                writeCharFile(tempPtr, ch_B);
                writeCharFile(tempPtr, ch_A);
                break;
            }
        }
    }
    if (flag == 0)
    {
        writeCharFile(tempPtr, ch_B);
    }

    fclose(tempPtr);
    fclose(ptr);
    remove(tableName);
    rename("T", tableName);

    return 1;
}
int updateRecord(char *tableName, char *searchFor, char *searchValue, char *updateFor, char *updateValue)
{
    FILE *ptr, *tempPtr;
    int searchIndex, updateIndex, flag, count = 0, matchFound, temp;
    char ch[DATA_BUFF];
    ptr = fopen(tableName, "r");
    tempPtr = fopen("tempTable", "w");
    if (ptr == NULL)
    {
        // table was not found
        writeLog(1, "No such table found");
        fclose(ptr);
        return -1;
    }
    searchIndex = getSearchIndexValue(searchFor, ptr);
    updateIndex = getSearchIndexValue(updateFor, ptr);

    fseek(ptr, 0, SEEK_SET);
    fscanf(ptr, "%[^\n]s", &ch);
    fgetc(ptr);
    writeCharFile(tempPtr, ch);

    while (fscanf(ptr, "%[^\n]s", &ch) != EOF)
    {
        fgetc(ptr);
        matchFound = doesSearchValueMatch(searchValue, ch, searchIndex);
        if (matchFound == 1)
        {
            // Update the record.
            temp = updateIndex;
            flag = 0;
            for (int i = 0; i < strlen(ch); i++)
            {
                if (temp == 0 || ch[i] == ',')
                {
                    if (temp == 0)
                    {
                        fprintf(tempPtr, "%s", updateValue);
                        flag = 1;
                    }
                    else
                        flag = 0;
                    temp--;
                }
                if (flag == 0)
                    fprintf(tempPtr, "%c", ch[i]);
            }
            fprintf(tempPtr, "\n");
            count++;
        }
        else
            writeCharFile(tempPtr, ch);
    }

    fclose(ptr);
    fclose(tempPtr);
    remove(tableName);
    rename("tempTable", tableName);
    printf("[SUCCESS] %d records updated\n", count);
    return 1;
}
int searchRecord(char *tableName, char *searchFor, char *searchValue)
{
    FILE *ptr;
    char ch[DATA_BUFF];
    int searchIndex, matchCount = 0, matchFound;
    ptr = fopen(tableName, "r");
    if (ptr == NULL)
    {
        // table was not found
        writeLog(1, "No such table found");
        fclose(ptr);
        return -1;
    }

    searchIndex = getSearchIndexValue(searchFor, ptr);
    while (fscanf(ptr, "%[^\n]s", &ch) != EOF)
    {
        matchFound = doesSearchValueMatch(searchValue, ch, searchIndex);
        if (matchFound == 1)
            printf("%s\n", ch);
        fgetc(ptr);
    }
    fclose(ptr);
    return 1;
}
int deleteRecord(char *tableName, char *searchFor, char *searchValue)
{
    FILE *ptr, *tempPtr;
    int searchIndex, count = 0, matchFound;
    char ch, ch1[DATA_BUFF];

    ptr = fopen(tableName, "r");
    tempPtr = fopen("tempTable", "w");
    if (ptr == NULL)
    {
        // table was not found
        writeLog(1, "No such table found");
        fclose(ptr);
        return -1;
    }

    searchIndex = getSearchIndexValue(searchFor, ptr);

    // Writing header
    fseek(ptr, 0, SEEK_SET);
    fscanf(ptr, "%[^\n]s", &ch1);
    fgetc(ptr);
    writeCharFile(tempPtr, ch1);

    while (fscanf(ptr, "%[^\n]s", &ch1) != EOF)
    {
        fgetc(ptr);
        matchFound = doesSearchValueMatch(searchValue, ch1, searchIndex);
        if (matchFound == -1)
            writeCharFile(tempPtr, ch1);
        else
            count++;
    }

    fclose(ptr);
    fclose(tempPtr);
    remove(tableName);
    rename("tempTable", tableName);
    printf("[SUCCESS] %d records removed\n", count);
    return 1;
}

// Helper function;
int getSearchIndexValue(char *searchFor, FILE *ptr)
{
    int matchCount = 0, currIndexCount = 0, lenSearchFor = strlen(searchFor);
    char ch;
    fseek(ptr, 0, SEEK_SET);
    do
    {
        ch = fgetc(ptr);
        if (ch == ',')
        {
            currIndexCount++;
            matchCount = 0;
        }
        else if (ch == searchFor[matchCount])
            matchCount++;
        else
            matchCount = 0;
        if (matchCount == lenSearchFor)
        {
            return currIndexCount;
        }
    } while (ch != '\n');
    return -1;
}
int doesSearchValueMatch(char *searchValue, char *ch, int searchIndex)
{
    int matchCount = 0;
    for (int i = 0; i < strlen(ch); i++)
    {
        if (ch[i] == ',')
            searchIndex--;
        else if (searchIndex == 0)
        {
            if (ch[i] == searchValue[matchCount])
                matchCount++;
            else
                matchCount = 0;
            if (matchCount == sizeof(searchValue) - 1)
                return 1;
        }
    }
    return -1;
}
void writeCharFile(FILE *ptr, char *data)
{
    for (int i = 0; i < strlen(data); i++)
        fprintf(ptr, "%c", data[i]);
    fprintf(ptr, "\n");
}
