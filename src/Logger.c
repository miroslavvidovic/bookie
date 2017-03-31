#include <stdio.h>
#include <time.h>

/**
 * Timestamp generator
 */
const char *timestamp()
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char *timestamp = asctime(tm);
    return (timestamp);
}

/**
 * Logger
 * data - log message
 * status - log status [ERROR]
 */
void logger(const char *data, char *status)
{
    FILE *log = NULL;
    const char *tstamp = timestamp();

    log = fopen("/home/miroslav/bookie/bookie.log", "a");
    if (log == NULL)
    {
        printf("Error! can't open log file.");
        /*TODO: Exit here */
        /* return -1; */
    }

    fprintf(log, "[%s] %s |-> %s\n", status, tstamp, data);
    fclose(log);
}
