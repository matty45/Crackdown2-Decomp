// GOM::cPointOfInterest (Crackdown 2): STAND-IN. Name and size (0x30, 16-byte aligned for its Vec3) from RuffKing's
// GameObjectManager/cPointOfInterest.h. CD2's cHelicopter::RetPointOfInterest (0x826BDCC8) steps through its inline
// array 0x30 bytes at a time. The members are not modelled.
#ifndef GOM_CPOINTOFINTEREST_H
#define GOM_CPOINTOFINTEREST_H

#include "cd2/layout.h"
#include "fun_runtime/vec3.h"

namespace GOM
{
    class cPointOfInterest
    {
    private:
        Fun_Runtime::Vec3 m_vLocalPos;                     // 0x0
        unsigned char m_unmodelled10[0x30 - 0x10];

        CD2_LAYOUT_CHECKS(cPointOfInterest,
            CD2_SIZE(cPointOfInterest, 0x30))
    };
}

#endif // GOM_CPOINTOFINTEREST_H
