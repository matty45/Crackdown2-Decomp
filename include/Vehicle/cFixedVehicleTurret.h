// Vehicle::cFixedVehicleTurret (Crackdown 2): STAND-IN. RuffKing's cFixedVehicleTurret.h names the class, its four
// virtuals (CD2 table 0x82001104 has four) and the fields through 0x60. CD2's constructor (0x826B7D50, out of line:
// cAgencyTank's constructor calls it) also clears words at 0x7C and 0x80, and cAgencyTank places the next member at
// +0x90, so CD2's class is 0x90 bytes; RuffKing's is 0x80. No destructor: cAgencyTank's deleting destructor does not
// call one.
#ifndef VEHICLE_CFIXEDVEHICLETURRET_H
#define VEHICLE_CFIXEDVEHICLETURRET_H

#include "cd2/layout.h"
#include "fun_runtime/vec3.h"

namespace PLAYER { class cPlayer; }
namespace AI { class cAiPlayer; }

namespace Vehicle
{
    class cFixedVehicleTurret
    {
    public:
        cFixedVehicleTurret();                                          // CD2 0x826B7D50
        virtual void UpdateTargetForPlayer(PLAYER::cPlayer *pPlayer);   // 0x826B80C0
        virtual void UpdateTargetForAI(AI::cAiPlayer *pAiPlayer);       // 0x826B7FF8
        virtual bool AICanFire(AI::cAiPlayer *pAiPlayer);               // 0x826B7E00
        virtual Fun_Runtime::Vec3 RetCrosshairOffset();                 // 0x826B7D28
        // RuffKing's names. CD2's ReplicateFields (0x826B7E88) takes a flag the references lack: while it is set, values
        // received from the network are not applied (the name is ours). cAgencyTank passes false.
        void ReplicateInitialFields();                                  // 0x826B7E18
        void ReplicateFields(bool bIgnoreReceived);

    private:
        float m_fTurretYaw;                                 // 0x10
        float m_fTurretPitch;
        float m_fYawRate;
        float m_fPitchRate;
        float m_fMinPitch;                                  // 0x20
        float m_fMaxPitch;
        float m_fMinYawRate;
        float m_fMaxYawRate;
        float m_fTargetYaw;                                 // 0x30
        float m_fTargetPitch;
        float m_fYawInterpRate;
        float m_fPitchInterpRate;
        bool m_bHasTarget;                                  // 0x40
        bool m_bFiring;                                     // 0x41
        Fun_Runtime::Vec3 m_vCurrentTarget;                 // 0x50
        Fun_Runtime::Vec3 m_vCrosshairOffset;               // 0x60
        unsigned char m_unmodelled70[0x90 - 0x70];

        CD2_LAYOUT_CHECKS(cFixedVehicleTurret,
            CD2_SIZE(cFixedVehicleTurret, 0x90)
            CD2_OFFSET(cFixedVehicleTurret, m_fTurretYaw, 0x10)
            CD2_OFFSET(cFixedVehicleTurret, m_bFiring, 0x41)
            CD2_OFFSET(cFixedVehicleTurret, m_vCrosshairOffset, 0x60))
    };
}

#endif // VEHICLE_CFIXEDVEHICLETURRET_H
