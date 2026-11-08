/* STAND-IN: names are ours. CD2's Lua-cache installer at 0x82770F48 passes
 * each record's start to lua_pushstring; lookup at 0x8293B0D8 reads its hash
 * at 0x104 and walks records by 0x110. The stream setup at 0x8293B198 reads
 * the payload offset and size at 0x108/0x10C. This is a serialized record.
 */
#ifndef CD2_LUA_ARCHIVE_ENTRY_H
#define CD2_LUA_ARCHIVE_ENTRY_H
#include "cd2/layout.h"

typedef struct lua_ArchiveEntry {
  char filename[260];
  unsigned int hash;
  unsigned int offset;
  unsigned int size;
#ifdef __cplusplus
  CD2_LAYOUT_CHECKS(lua_ArchiveEntry,
    CD2_SIZE(lua_ArchiveEntry, 0x110)
    CD2_OFFSET(lua_ArchiveEntry, filename, 0)
    CD2_OFFSET(lua_ArchiveEntry, hash, 0x104)
    CD2_OFFSET(lua_ArchiveEntry, offset, 0x108)
    CD2_OFFSET(lua_ArchiveEntry, size, 0x10C))
#endif
} lua_ArchiveEntry;
#endif
