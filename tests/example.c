/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <admin@hypothermic.nl> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * -----------------------------------------------------------------------------
 */

#include "../log.h"

int main()
{
    logstream_t *stream = log_stream_new();

    log(stream, "Hello world!");

    // --- 1. Select between output streams --- //

    stream->def_stream = STDERR;
    log(stream, "This gets logged to stderr.");

    stream->def_stream = STDOUT;
    log(stream, "This gets logged to stdout.");

    // --- 2. Muting the stream --- //

    stream->muted = true;
    log(stream, "This doesn't get logged because we muted the stream.");

    stream->muted = false;
    log(stream, "This does get logged because we unmuted the stream.");

    // --- 3. Time and date position --- //

    stream->frm_revert = true;
    log(stream, "Time and date are reverted");

    stream->frm_revert = false;
    log(stream, "Time and date are normal");

    // --- 4. Time and date formats --- //

    stream->time_format = TF_NONE;
    log(stream, "No time stamp is shown");

    stream->time_format = SS_MM_HH;
    log(stream, "Time stamp is shown in SS_MM_HH");

    stream->time_format = HH_MM_SS;
    log(stream, "Time stamp is shown in HH_MM_SS");


    stream->time_format = TF_NONE;
    stream->date_format = DF_NONE;
    log(stream, "No time or date stamp is shown");


    stream->time_format = HH_MM_SS;
    stream->date_format = DF_NONE;
    log(stream, "No date stamp is shown");

    stream->date_format = YYYY;
    log(stream, "Date stamp is shown in YYYY");

    stream->date_format = YYYY_MM;
    log(stream, "Date stamp is shown in YYYY_MM");

    stream->date_format = YYYY_MM_DD;
    log(stream, "Date stamp is shown in YYYY_MM_DD");

    stream->date_format = YYYY_DD_MM;
    log(stream, "Date stamp is shown in YYYY_DD_MM");

    // --- 5. Calling from other_function --- //

    other_function(stream);

    // --- 6. Async logging --- //
    loga(stream, "This message is being logged asynchronously");
}

void other_function(logstream_t *stream)
{
    log(stream, "This is being logged from another function");
}