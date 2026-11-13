// CD2 Lua C API: reuse the published 5.0.2 header with the game's float number ABI.
// The float configuration is independently verified by all matched Lua middleware functions.
#ifndef CD2_LUA_C_API_H
#define CD2_LUA_C_API_H

#define LUA_NUMBER float
extern "C" {
#include "../../src/middleware/lua/lua.h"
}

#endif // CD2_LUA_C_API_H
