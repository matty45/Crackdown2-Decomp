#include "rws/attributes.h"
// GangManager::cAgressiveResponseTurretVehicleSetup (Crackdown 2): STAND-IN with only what its matched functions need; its bases are not modelled yet.
// Its class-factory registrar (0x82FDBE70) registers "cAgressiveResponseTurretVehicleSetup" with MakeNew (0x82672A40) and size 0x68.
#ifndef GANGMANAGER_CAGRESSIVERESPONSETURRETVEHICLESETUP_H
#define GANGMANAGER_CAGRESSIVERESPONSETURRETVEHICLESETUP_H

namespace GangManager
{
    class cAgressiveResponseTurretVehicleSetup
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // GANGMANAGER_CAGRESSIVERESPONSETURRETVEHICLESETUP_H
