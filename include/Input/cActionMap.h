// STAND-IN storage only. CD2 ApplyLeftHanded indexes two maps with stride 0x7F8;
// the reference cGameControlManager names this array m_SPActionMap. Internal map layout is unmodelled.
#ifndef INPUT_CACTIONMAP_H
#define INPUT_CACTIONMAP_H
#include "cd2/layout.h"
namespace Input
{
    class cActionMap
    {
        unsigned char m_unmodelled[0x7F8];
    public:
        CD2_LAYOUT_CHECKS(cActionMap, CD2_SIZE(cActionMap, 0x7F8))
    };
}
#endif
