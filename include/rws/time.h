// RWS game-time access shared by ambient VFX and network spawn points.
// CD2 0x8284C508/0x8284C570 use the stored-time flag at 0x83800FB9,
// stored milliseconds at 0x8377ADD0, and fallback 0x82954E48. Names are ours.
#ifndef RWS_TIME_H
#define RWS_TIME_H

namespace RWS
{
    namespace Time
    {
        extern unsigned char g_bUseStoredTime;
        extern unsigned int g_nStoredTime;
        unsigned int CalcGameTime();
        inline unsigned int RetGameTime() { return g_bUseStoredTime ? g_nStoredTime : CalcGameTime(); }
    }
}

#endif // RWS_TIME_H
