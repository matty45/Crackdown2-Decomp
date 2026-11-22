// Burn/RuffKing field names and layout. CD2 MakeNew 0x82672A40 clears the
// three arrays at object +0x34/+0x40/+0x4C and the remaining template fields.
#pragma once
#include "cd2/layout.h"
namespace GOM { class cObjectPrototype; }
namespace GangManager
{
    struct tAgressiveResponseTurretTeamTemplate
    {
        static const int nMAX_TURRET_PROTOTYPES = 3;
        static const unsigned int nINVALID_AR_INDEX = ~0U;
        GOM::cObjectPrototype *pVehiclePrototype;
        unsigned int nNumTurrets;
        GOM::cObjectPrototype *apTurretPrototypes[nMAX_TURRET_PROTOTYPES];
        GOM::cObjectPrototype *apWeaponPrototypes[nMAX_TURRET_PROTOTYPES];
        GOM::cObjectPrototype *apGunnerPrototypes[nMAX_TURRET_PROTOTYPES];
        GOM::cObjectPrototype *pDriverPrototype;
        unsigned int nARTurretIndex;

        CD2_LAYOUT_CHECKS(tAgressiveResponseTurretTeamTemplate,
            CD2_SIZE(tAgressiveResponseTurretTeamTemplate, 0x34)
            CD2_OFFSET(tAgressiveResponseTurretTeamTemplate, pVehiclePrototype, 0)
            CD2_OFFSET(tAgressiveResponseTurretTeamTemplate, nNumTurrets, 4)
            CD2_OFFSET(tAgressiveResponseTurretTeamTemplate, apTurretPrototypes, 8)
            CD2_OFFSET(tAgressiveResponseTurretTeamTemplate, apWeaponPrototypes, 0x14)
            CD2_OFFSET(tAgressiveResponseTurretTeamTemplate, apGunnerPrototypes, 0x20)
            CD2_OFFSET(tAgressiveResponseTurretTeamTemplate, pDriverPrototype, 0x2C)
            CD2_OFFSET(tAgressiveResponseTurretTeamTemplate, nARTurretIndex, 0x30))
    };
}
