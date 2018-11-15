/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <admin@hypothermic.nl> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * -----------------------------------------------------------------------------
 */

#ifndef LIBLOGHT_H_
#define LIBLOGHT_H_

#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#include <pthread.h>

#define LIBLOGHT_VERSION ((int) 7)

typedef enum 
{
    false,
    true
} _boolean_t;

#define _GNU_SOURCE /* See feature_test_macros(7) */

typedef enum 
{
    STDOUT,
    STDERR
} logdefstream_t;

typedef enum
{
    DF_NONE,

    YYYY,
    YYYY_MM,
    YYYY_MM_DD,
    YYYY_DD_MM,

    MM_YYYY,
    MM_DD_YYYY,
    DD_MM_YYYY
} logdateformat_t;

typedef enum
{
    TF_NONE,

    HH_MM_SS,
    SS_MM_HH
} logtimeformat_t;

typedef struct _logstream_t
{
    _boolean_t *muted;
    _boolean_t *frm_revert; // TODO
    _boolean_t *caller_show; // TODO
    //_time_offset_t time_offset; // TODO

    logdateformat_t *date_format;
    logtimeformat_t *time_format;
    logdefstream_t *def_stream;
} logstream_t;

static struct _log_args
{
    logstream_t *stream;
    const char* msg;
    const char* file_name;
    int line; 
    const char* caller_name;
};

#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch"

static char *_format_time(struct tm *timestc, logstream_t *stream)
{
    char *buf;
    // TODO: check if asprintf is availible (GNU or BSD only??)
    // TODO: switch regexes by logtimeformat_t
    asprintf(&buf, "%02d:%02d:%02d", timestc->tm_hour, timestc->tm_min, timestc->tm_sec);
    return buf;
}

static char *_format_date(struct tm *timestc, logstream_t *stream)
{
    char *buf;
    // idem ^^
    asprintf(&buf, "%02d-%02d-%02d", timestc->tm_mday, timestc->tm_mon + 1, timestc->tm_year + 1900);
    return buf;
}

void log(logstream_t *stream, const char* msg, const char* file_name, int line, const char* caller_name)
{
    if (!stream->muted)
    {
        time_t rawtime;
        struct tm *timeinfo;

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        // TODO: seperator styles (" ", "-", "::") and ability to hide file name, line no, etc.
        fprintf(stream->def_stream ? stderr : stdout, "[%s %s] %s:%d %s(): %s\n", stream->frm_revert ? _format_date(timeinfo, stream) : _format_time(timeinfo, stream), 
                                                                                  stream->frm_revert ? _format_time(timeinfo, stream) : _format_date(timeinfo, stream),
                                                                                  file_name,
                                                                                  line,
                                                                                  caller_name,
                                                                                  msg);
    }
}

static void *_log_asu(void *args)
{
    struct _log_args *wrapper = args;

    log(wrapper->stream, wrapper->msg, wrapper->file_name, wrapper->line, wrapper->caller_name);
}

#define log(stream, msg) log(stream, msg, __FILE__, __LINE__, __func__)

void loga(logstream_t *stream, const char* msg, const char* file_name, int line, const char* caller_name)
{
    pthread_t thread;
    struct _log_args *args = (struct _log_args*)malloc(sizeof(struct _log_args));

    args->stream = stream;
    args->msg = msg;
    args->file_name = file_name;
    args->line = line;
    args->caller_name = caller_name;
    int res = pthread_create(&thread, NULL, _log_asu, &args);
    printf("res=%d join=%d", res, pthread_join(thread, NULL));
}

#define loga(stream, msg) loga(stream, msg, __FILE__, __LINE__, __func__)

#pragma GCC diagnostic pop

logstream_t *log_stream_new()
{
    logstream_t *res = (logstream_t*)malloc(sizeof(logstream_t));
    res->muted = false;
    res->date_format = DF_NONE;
    res->time_format = TF_NONE;
    res->def_stream = STDOUT;
    return res;
}

void log_stream_free(logstream_t *stream)
{
    free(stream);
}

int log_lib_version()
{
    return LIBLOGHT_VERSION;
}

#endif // LIBLOGHT_H