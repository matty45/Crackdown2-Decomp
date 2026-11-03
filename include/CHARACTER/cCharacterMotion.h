// STAND-IN: RuffKing cCharacterMotion derives from cNetDynamicBody. CD2's
// descriptor at 0x8229FDC8 gives size 0x11F0; fields beyond the 0x7A0 base are unmodelled.
#ifndef CHARACTER_CCHARACTERMOTION_H
#define CHARACTER_CCHARACTERMOTION_H
#include "PHYSICS/cNetDynamicBody.h"
namespace CHARACTER
{
    class cCharacterMotion : public PHYSICS::cNetDynamicBody
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
    private:
        unsigned char m_unmodelled7A0[0x11F0 - 0x7A0];
        CD2_LAYOUT_CHECKS(cCharacterMotion, CD2_SIZE(cCharacterMotion, 0x11F0))
    };
}
#endif
