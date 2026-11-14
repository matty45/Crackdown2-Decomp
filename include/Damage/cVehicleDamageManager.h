// Damage::cVehicleDamageManager (Crackdown 2): STAND-IN. Name, own vtable (RuffKing's first virtual is Init) and member
// names from RuffKing's Damage/cVehicleDamageManager.h. CD2's cVehicle::ArbitrateOwnership (0x826DEF78) reads
// m_nBrakeUpState at 0xE8, RuffKing's offset. Only that member and m_pVehicle are modelled; the complete size and the
// virtuals' bodies are not.
#ifndef DAMAGE_CVEHICLEDAMAGEMANAGER_H
#define DAMAGE_CVEHICLEDAMAGEMANAGER_H

#include "cd2/layout.h"

namespace Vehicle { class cVehicle; }

namespace Damage
{
    class cVehicleDamageManager
    {
    public:
        virtual void Init(Vehicle::cVehicle *pVehicle);
    protected:
        Vehicle::cVehicle *m_pVehicle;                  // 0x4
    private:
        unsigned char m_unmodelled8[0xE8 - 0x8];
    public:
        unsigned char m_nBrakeUpState;                  // 0xE8

        CD2_LAYOUT_CHECKS(cVehicleDamageManager,
            CD2_OFFSET(cVehicleDamageManager, m_pVehicle, 4)
            CD2_OFFSET(cVehicleDamageManager, m_nBrakeUpState, 0xE8))
    };
}

#endif // DAMAGE_CVEHICLEDAMAGEMANAGER_H
