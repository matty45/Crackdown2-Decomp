// AI::cCharacterBrain (Crackdown 2): STAND-IN for the AI brain a character interface drives (cCharacterEntityIF's
// m_pCharacterBrain, 0x508). RuffKing's class (Kaim::CBrain base) gives the names of the flags CD2's script methods
// on cCharacterEntityIF set and read: "SetAiming" (0x823F4748) stores the byte at 0x20, "CrouchImmediately" /
// "UncrouchImmediately" (0x823F4718 / 0x823F4728) set and clear 0x21 and "IsTryingToCrouch" (0x823F4738) returns it,
// "DropImmediately" (0x823F46F8) clears 0x23 and "ExitVehicleImmediately" (0x823F4708) clears 0x24, which the
// ForceIntoVehicle/ForceOutOfVehicle overrides (0x823F46C0 / 0x823F46D0) set and clear. RuffKing has the same flags in
// the same order four bytes later (m_bAiming 0x24, m_bCrouching, m_bCovering, m_bCarrying, m_bInVehicle 0x28). CD2
// inlines each accessor, so they are inline here. The Kaim::CBrain base and the storage before 0x20 are not modelled.
#ifndef AI_CCHARACTERBRAIN_H
#define AI_CCHARACTERBRAIN_H

#include "cd2/layout.h"

namespace AI
{
    class cCharacterBrain
    {
    public:
        bool IsTryingToCrouch() { return m_bCrouching; }
        void CrouchImmediately() { m_bCrouching = true; }
        void UncrouchImmediately() { m_bCrouching = false; }
        void DropImmediately() { m_bCarrying = false; }
        void SetAiming(bool bAiming) { m_bAiming = bAiming; }
        void SetInVehicle(bool bInVehicle) { m_bInVehicle = bInVehicle; }

    private:
        unsigned char m_unmodelled0[0x20];
        bool m_bAiming;                 // 0x20
        bool m_bCrouching;              // 0x21
        bool m_bCovering;               // 0x22
        bool m_bCarrying;               // 0x23
        bool m_bInVehicle;              // 0x24

        CD2_LAYOUT_CHECKS(cCharacterBrain,
            CD2_OFFSET(cCharacterBrain, m_bAiming, 0x20)
            CD2_OFFSET(cCharacterBrain, m_bCrouching, 0x21)
            CD2_OFFSET(cCharacterBrain, m_bCarrying, 0x23)
            CD2_OFFSET(cCharacterBrain, m_bInVehicle, 0x24))
    };
}

#endif // AI_CCHARACTERBRAIN_H
