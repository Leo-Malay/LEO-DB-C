#include <stdio.h>
#include <time.h>
#include "table.c"
#include "record.c"
#include "log.c"
int main()
{
    clock_t start, end;
    char *tableName = "data/Card";

    // Starting to measure time.
    createTable(tableName, 4, "fname", "lname", "email", "mobile");
    start = clock();
    /*
    for (int i = 0; i < 100; i++)
    {
        insertRecord(tableName, 4, "Het", "Bhavsar", "het@gmail.com", "9426217367");
        insertRecord(tableName, 4, "Katty", "Perry", "katty@gmail.com", "9587453423");
        insertRecord(tableName, 4, "Malay", "Bhavsar", "het@gmail.com", "9426217367");
        insertRecord(tableName, 4, "John", "Doe", "john@gmail.com", "8989677889");
        insertRecord(tableName, 4, "Sarah", "Perry", "katty@gmail.com", "9587453423");
        insertRecord(tableName, 4, "Krishna", "Bhavsar", "krishna@gmail.com", "9426217367");
        insertRecord(tableName, 4, "Mahima", "Patel", "Mahima@gmail.com", "9587453423");
        insertRecord(tableName, 4, "Umang", "Ghadvi", "Umang@gmail.com", "9426217367");
        insertRecord(tableName, 4, "Ali", "Khan", "alj@gmail.com", "8989677889");
        insertRecord(tableName, 4, "Ali", "Khan", "ali@gmail.com", "8989677889");
        insertRecord(tableName, 4, "Ammar", "Malik", "ammar@gmail.com", "9587453423");
    }
    */
    // searchRecord(tableName, "fname", "Zeel");
    // searchRecord(tableName, "email", "zeel@gmail.com");
    /*
    searchRecord("iCard", "fname", "Malay");
    searchRecord("iCard", "email", "krishan@gmail.com");
    searchRecord("iCard", "lname", "Khan");
    searchRecord("iCard", "mobile", "Malay");
    */
    // deleteRecord(tableName, "fname", "Umang");
    /*
     deleteRecord("iCard", "mobile", "8989677889");
     */
    // updateRecord("iCard", "fname", "Umang", "mobile", "9786756434");
    // updateRecord(tableName, "fname", "Saprah", "email", "sph@gmail.co.in");
    // updateRecord(tableName, "fname", "Zeel", "email", "zeal123@gmail.com");
    // searchRecord("iCard", "email", "het@gmail.com");
    // searchRecord("iCard", "lname", "Bhavsar");
    end = clock();
    printf("Time Taken: %f\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    return 0;
}