// Vehicle::cVehicleTurret (Crackdown 2): STAND-IN. Name, size (0x88) and member names from RuffKing's
// Vehicle/cVehicleTurret.h. cVehicle keeps three of them inline (m_VehicleTurrets, Vehicle/cVehicle.h); CD2's
// RetVehicleTurret (0x826D5020) steps through them 0x88 bytes at a time and tests the turret safe pointer's payload at
// +0x7C, RuffKing's m_pTurret (0x70). Only that pointer is modelled.
#ifndef VEHICLE_CVEHICLETURRET_H
#define VEHICLE_CVEHICLETURRET_H

#include "cd2/layout.h"
#include "fun_runtime/safedeletablepointer.h"
#include "Prop/cTurretBase.h"

namespace Vehicle
{
    class cVehicleTurret
    {
    public:
        cVehicleTurret();
        ~cVehicleTurret();
        // Inlined by CD2 into cVehicle::RetVehicleTurret.
        Prop::cTurretBase *RetTurret() { return m_pTurret; }

    protected:
        unsigned char m_unmodelled0[0x70];
        Fun_Runtime::cSafeDeletablePointer<Prop::cTurretBase> m_pTurret;   // 0x70
        unsigned char m_unmodelled80[0x88 - 0x80];

        CD2_LAYOUT_CHECKS(cVehicleTurret,
            CD2_SIZE(cVehicleTurret, 0x88)
            CD2_OFFSET(cVehicleTurret, m_pTurret, 0x70))
    };
}

#endif // VEHICLE_CVEHICLETURRET_H
