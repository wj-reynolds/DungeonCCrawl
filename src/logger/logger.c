#include "logger/logger.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool timeOnly;

static char* timestamp()
{
    time_t now;
    time(&now);

    const struct tm *timeinfo = localtime(&now);

    char* stamp = malloc(sizeof(char) * 100);

    if (timeOnly) {
        sprintf(stamp, "%02d:%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    } else {
        sprintf(stamp, "%d/%d/%d %d:%d:%d", timeinfo->tm_mday, timeinfo->tm_mon, timeinfo->tm_year,
            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    }

    return stamp;
}

void setDateAndTime(const bool dateAndTime)
{
    timeOnly = !dateAndTime;
}

void log_(const LogLevel level, const char* format, ...)
{
    va_list args;
    va_start(args, format);

    char* stamp = timestamp();

    switch (level) {
        case FATAL:
            fprintf(stderr, "[%s - ", stamp);
            fprintf(stderr, "[FATAL]\t");
            vfprintf(stderr, format, args);
            break;
        case ERROR:
            fprintf(stderr, "[%s - ", stamp);
            fprintf(stderr, "ERROR]\t");
            vfprintf(stderr, format, args);
            break;
        case WARNING:
            printf("[%s - ", stamp);
            printf("WARNING]\t");
            vprintf(format, args);
            break;
        case INFO:
            printf("[%s - ", stamp);
            printf("INFO]\t");
            vprintf(format, args);
            break;
        case DEBUG:
            printf("[%s - ", stamp);
            printf("DEBUG]\t");
            vprintf(format, args);
            break;
        case TRACE:
            printf("[%s - ", stamp);
            printf("TRACE]\t");
            vprintf(format, args);
            break;
    }

    free(stamp);
    va_end(args);
}
