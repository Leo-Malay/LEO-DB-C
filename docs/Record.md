# List of Operations and Algorithms for Records

### Insert

1. Create temp file(Ref. T)
2. Copy headers from original file(Ref. A) to T.
3. Read record from A.
4. Compare record with data to be inserted
5. If record is chronologically smaller than data, write record to T.
6. Repeat step 3 to 5 until found a larger record.
7. Write data to T.
8. If there are remaining records in A.
9. Read record from A and write to B.
10. Remove the A.
11. Rename T to A.

### Search

1. Open data file(Ref. A)
2. Read headers from A.
3. Get index from searchFor parameter and header.
4. Read records one by one.
5. Compare with search value.
6. If match found then output to console.
7. Repeat steps 4 and 6 till EOF.

### Delete

1. Open data file(Ref. A) and Temp file(Ref. T)
2. Read headers from A.
3. Get index from searchFor parameter and header.
4. Read reocrds one by one from A.
5. Match records from A with required value.
6. If match found ignore the record.
7. If match not found write record to T.
8. Repeat steps 4 to 7 till EOF.

### Update

1. Open data file(Ref. A) and Temp file(Ref. T)
2. Read headers from A.
3. Get index from searchFor and updateFor parameter and header.
4. Read reocrds one by one from A.
5. Match records from A with required value.
6. If match found update the data at index updateIndex and write new record to T.
7. If match not found write record to T.
8. Repeat steps 4 to 7 till EOF.
