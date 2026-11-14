// Vehicle::cLVDamageEffect (Crackdown 2): STAND-IN. Name and member name from RuffKing's Vehicle/cLVDamageEffect.h
// (0x19C bytes, m_bIsAWheelDamaged at 0x195). cLandVehicle holds one at 0x1B58 (its destructor 0x826C2458 calls
// 0x827016C0 there); CD2's cLandVehicle::IsFunctionallyDamaged (0x826C25D8) reads the flag at +0x199, four bytes above
// RuffKing's, so the size is taken as RuffKing's plus those four bytes. Only the flag is modelled.
#ifndef VEHICLE_CLVDAMAGEEFFECT_H
#define VEHICLE_CLVDAMAGEEFFECT_H

#include "cd2/layout.h"

namespace Vehicle
{
    class cLVDamageEffect
    {
    public:
        ~cLVDamageEffect();                             // CD2 0x827016C0
        // RuffKing's (out of line there); CD2 inlines it.
        bool IsAWheelDamaged() { return m_bIsAWheelDamaged; }

    private:
        unsigned char m_unmodelled0[0x199];
        bool m_bIsAWheelDamaged;                        // 0x199
        unsigned char m_unmodelled19A[0x1A0 - 0x19A];

        CD2_LAYOUT_CHECKS(cLVDamageEffect,
            CD2_SIZE(cLVDamageEffect, 0x1A0)
            CD2_OFFSET(cLVDamageEffect, m_bIsAWheelDamaged, 0x199))
    };
}

#endif // VEHICLE_CLVDAMAGEEFFECT_H
