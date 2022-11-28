### LEO-DB-C (Ultra Basic DB implementation in C)

# By Malay Bhavsar

<p>This database program stores data in form of CSV. Inserted values are sorted in th chronological order given priority to the first field and so on. It is still under development. I will be adding multiple features over time.</p>
<small>NOTE: By no means does this program is full proof. It was created for learning purpose and it should never be used in any means as a part of production software.<small>

<a href="https://github.com/Leo-Malay/LEO-DB-C/blob/master/docs/Record.md">Algorithm for operations</a>

### COMPILE AND RUN

write all the functions you need in the main.c file and perform the operations.

```c
    $ gcc main.c -o main.exe
    $ ./main
```

### Create a Table.

```c
    createTable(TABLE_NAME, NUMBER_COLUMN, COL_1, COL_2, ...);
```

### Destroy a Table.

```c
    deleteTable(TABLE_NAME);
```

### Insert Record.

```c
    insertRecord(TABLE_NAME, NUMBER_COLUMN, COL_DATA_1, COL_DATA_2, ...);
```

### Update Record.

```c
    updateRecord(TABLE_NAME, SEARCH_FOR, SEARCH_VALUE, UPDATE_FOR, UPDATE_VALUE);
```

### Search Record.

```c
    searhRecord(TABLE_NAME, SEARCH_FOR, SEARCH_VALUE);
```

### Delete Record.

```c
    deleteRecord(TABLE_NAME, SEARCH_FOR, SEARCH_VALUE);
```
