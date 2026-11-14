// Damage::cVehicleDamageManager (Crackdown 2): STAND-IN. Name, own vtable (RuffKing's first virtual is Init) and member
// names from RuffKing's Damage/cVehicleDamageManager.h. CD2's cVehicle::ArbitrateOwnership (0x826DEF78) reads
// m_nBrakeUpState at 0xE8, RuffKing's offset; its complete size is RuffKing's 0x38C (cVehicle's at 0xD54 ends at
// m_pExplosionInstigator, 0x10E0). Its destructor is compiler-generated, as RuffKing's: cVehicle's (0x826CE0E8)
// destroys only m_DMManager. Only those members and m_pVehicle are modelled; the virtuals' bodies are not.
#ifndef DAMAGE_CVEHICLEDAMAGEMANAGER_H
#define DAMAGE_CVEHICLEDAMAGEMANAGER_H

#include "cd2/layout.h"
#include "Damage/cDamageMorphManager.h"

namespace Vehicle { class cVehicle; }

namespace Damage
{
    class cVehicleDamageManager
    {
    public:
        virtual void Init(Vehicle::cVehicle *pVehicle);
    protected:
        Vehicle::cVehicle *m_pVehicle;                  // 0x4
        cDamageMorphManager m_DMManager;                // 0x8
    private:
        unsigned char m_unmodelled94[0xE8 - 0x94];
    public:
        unsigned char m_nBrakeUpState;                  // 0xE8
    private:
        unsigned char m_unmodelledE9[0x38C - 0xE9];
    public:

        CD2_LAYOUT_CHECKS(cVehicleDamageManager,
            CD2_SIZE(cVehicleDamageManager, 0x38C)
            CD2_OFFSET(cVehicleDamageManager, m_pVehicle, 4)
            CD2_OFFSET(cVehicleDamageManager, m_DMManager, 8)
            CD2_OFFSET(cVehicleDamageManager, m_nBrakeUpState, 0xE8))
    };
}

#endif // DAMAGE_CVEHICLEDAMAGEMANAGER_H
