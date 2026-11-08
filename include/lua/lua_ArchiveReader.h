/* STAND-IN: names are ours. CD2's reader at 0x8293B1D0 consumes the pointer
 * range at 0/4 into a 512-byte buffer at 8, advancing the current pointer.
 */
#ifndef CD2_LUA_ARCHIVE_READER_H
#define CD2_LUA_ARCHIVE_READER_H
#include "cd2/layout.h"

typedef struct lua_ArchiveReader {
  const char *next;
  const char *end;
  char buffer[512];
#ifdef __cplusplus
  CD2_LAYOUT_CHECKS(lua_ArchiveReader,
    CD2_SIZE(lua_ArchiveReader, 0x208)
    CD2_OFFSET(lua_ArchiveReader, next, 0)
    CD2_OFFSET(lua_ArchiveReader, end, 4)
    CD2_OFFSET(lua_ArchiveReader, buffer, 8))
#endif
} lua_ArchiveReader;
#endif
