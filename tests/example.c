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
}