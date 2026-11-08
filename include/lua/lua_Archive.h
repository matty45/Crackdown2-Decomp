/* STAND-IN: CD2's serialized Lua archive; names are ours.
 * The installer at 0x82770F48 and lookup at 0x8293B0D8 establish a signed
 * count followed immediately by variable-length 0x110-byte records. Payload
 * bytes follow the record array (0x8293B198). The trailing [1] models the
 * variable-length serialized array, not the complete allocation size.
 */
#ifndef CD2_LUA_ARCHIVE_H
#define CD2_LUA_ARCHIVE_H

#include "lua/lua_ArchiveEntry.h"

typedef struct lua_Archive {
  int count;
  lua_ArchiveEntry entries[1];
#ifdef __cplusplus
  CD2_LAYOUT_CHECKS(lua_Archive,
    CD2_OFFSET(lua_Archive, count, 0)
    CD2_OFFSET(lua_Archive, entries, 4))
#endif
} lua_Archive;

#endif
