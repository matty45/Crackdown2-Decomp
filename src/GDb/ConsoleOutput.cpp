// GDb::ConsoleOutput, CD2 0x825D0CF0: retail formatting without console output.
// The reference builds also dispatch the buffer to CommonConsoleOutput; CD2
// retains only the bounded formatting call. IDA confirms 256 wchar_t elements,
// size argument 255, and the _TRUNCATE count. This body supplies LTCG with the
// real variadic callee information needed by its callers' stack frames.
#include "GDb/console.h"
#include <stdio.h>
#include <stdarg.h>

namespace GDb
{
    void ConsoleOutput(const wchar_t *fmt, ...)
    {
        wchar_t buffer[256];
        va_list args;
        va_start(args, fmt);
        _vsnwprintf_s(buffer, 255, _TRUNCATE, fmt, args);
        va_end(args);
    }
}
