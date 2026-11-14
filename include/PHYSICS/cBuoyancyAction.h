// PHYSICS::cBuoyancyAction (Crackdown 2): STAND-IN. Name and base (hkUnaryAction) from RuffKing's
// Physics/cBuoyancyAction.h. CD2's inlined cVehicle::IsSufficientlyInWater (in cVehicle::IsOkToInteract, 0x826D6FC8,
// and cHelicopter's, 0x826BDEB0) reads m_bInWater at 0x6A, one byte below RuffKing's offset. Only that flag is
// modelled; the complete size is not asserted.
#ifndef PHYSICS_CBUOYANCYACTION_H
#define PHYSICS_CBUOYANCYACTION_H

#include "cd2/layout.h"
#include "Havok/hkUnaryAction.h"

namespace PHYSICS
{
    class cBuoyancyAction : public hkUnaryAction
    {
    private:
        unsigned char m_unmodelled1C[0x6A - 0x1C];
    public:
        bool m_bInWater;                                // 0x6A

        CD2_LAYOUT_CHECKS(cBuoyancyAction,
            CD2_OFFSET(cBuoyancyAction, m_bInWater, 0x6A))
    };
}

#endif // PHYSICS_CBUOYANCYACTION_H
