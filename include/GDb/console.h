// GDb console output: signature from the RuffKing/Burn PDBs; CD2 body at
// 0x825D0CF0 formats a 256-wide-character buffer and discards the result.
#ifndef GDB_CONSOLE_H
#define GDB_CONSOLE_H
namespace GDb
{
    void ConsoleOutput(const wchar_t *fmt, ...);
}
#endif
