# log.h

```
[20:41:32 14-11-2018] main(): Hello world!
```

Every project needs a proper logging solution, but most don't come with simplicity.
Log.h is a flexible and customizable logging solution which is very easy to use.

## Features

- Easily log to a predefined stream
- Configure the time format and offset of a stream
- See the caller method of `log(...);`
- C99 compatible

## Example

```c
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
```

More examples are in the `tests` folder.

## Versioning

This library is aimed to always be backwards-compatible.
The function signatures will never be changed after the
function has been added to the library.

The predefined `LIBLOGHT_VERSION` integer in `log.h`
will be bumped every git commit which includes changes to
`log.h`