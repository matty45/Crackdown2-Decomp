// RenderWare memory/stream byte-order helpers as Crackdown 2's RW4/RWS code uses them.
// Stream data (e.g. RWS attribute payloads) is little-endian; on the big-endian Xbox 360 RwMemNative32 swaps it in place.
// The name follows the RenderWare API (RwMemNative32(void *mem, RwUInt32 size)). In RW 3.7 big-endian builds it is an
// out-of-line function, but CD2 inlines the swap (proven byte-exact by GangManager::cFactionConfigData::HandleAttributes),
// so it is defined inline here. The 32-bit swap helper's real name is unknown.
#ifndef RW_RWMEM_H
#define RW_RWMEM_H

inline unsigned int rwSwap32(unsigned int x)
{
    return (x >> 24) | ((x >> 8) & 0xFF00) | ((x << 8) & 0xFF0000) | (x << 24);
}

inline void RwMemNative32(void *mem, unsigned int size)
{
    (void)size;
    *(unsigned int *)mem = rwSwap32(*(unsigned int *)mem);
}

#endif // RW_RWMEM_H
