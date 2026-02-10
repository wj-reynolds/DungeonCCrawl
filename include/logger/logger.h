#pragma once

#ifndef LOG_WARNING_ENABLED
    #define LOG_WARNING_ENABLED 1
#endif

#ifndef LOG_INFO_ENABLED
    #define LOG_INFO_ENABLED 1
#endif

#ifndef LOG_DEBUG_ENABLED
    #define LOG_DEBUG_ENABLED 1
#endif

#ifndef LOG_TRACE_ENABLED
    #define LOG_TRACE_ENABLED 1
#endif

typedef enum LogLevel{
    FATAL,
    ERROR,
    WARNING,
    INFO,
    DEBUG,
    TRACE
} LogLevel;

void setDateAndTime(bool dateAndTime);
void log_(LogLevel level, const char* format, ...);

#define logFATAL(message, ...) log_(FATAL, message, ##__VA_ARGS__)

#define logERROR(message, ...) log_(ERROR, message, ##__VA_ARGS__)

#if LOG_WARNING_ENABLED == 1
#define logWARNING(message, ...) log_(WARNING, message, ##__VA_ARGS__)
#else
#define logWARNING(message, ...)
#endif

#if LOG_INFO_ENABLED == 1
#define logINFO(message, ...) log_(INFO, message, ##__VA_ARGS__)
#else
#define logINFO(message, ...)
#endif

#if LOG_DEBUG_ENABLED == 1
#define logDEBUG(message, ...) log_(DEBUG, message, ##__VA_ARGS__)
#else
#define logDEBUG(message, ...)
#endif

#if LOG_TRACE_ENABLED == 1
#define logTRACE(message, ...) log_(TRACE, message, ##__VA_ARGS__)
#else
#define logTRACE(message, ...)
#endif