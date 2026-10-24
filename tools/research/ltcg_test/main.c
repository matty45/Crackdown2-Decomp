#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

char *getenv(const char *name) { (void)name; return 0; }

void __cdecl main(void)
{
    lua_State *L = lua_open();
    luaopen_base(L);
    luaL_loadbuffer(L, "x=1", 3, "t");
    lua_pcall(L, 0, 0, 0);
    lua_close(L);
}
