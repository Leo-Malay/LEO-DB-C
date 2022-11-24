#include <stdio.h>
#include <time.h>

#ifndef LOG_C
#define LOG_C
#define LOG_FILE_DEST "log/log.txt"
void writeLog(int type, char *message)
{
    FILE *ptr;
    char *logtype;
    switch (type)
    {
    case 1:
        logtype = "ERROR";
        break;
    case 2:
        logtype = "WARN";
        break;
    case 3:
        logtype = "SUCCESS";
        break;
    default:
        logtype = "RANDOM";
        break;
    }
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("[%s] [%02d-%02d-%d %02d:%02d:%02d] %s\n", logtype, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec, message);
    ptr = fopen(LOG_FILE_DEST, "a");
    fprintf(ptr, "[%s] [%02d-%02d-%d %02d:%02d:%02d] %s\n", logtype, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec, message);
    fclose(ptr);
}

#endif