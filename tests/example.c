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

    // --- 4. Calling from other_function --- //

    other_function(stream);
}

void other_function(logstream_t *stream)
{
    log(stream, "This is being logged from another function");
}