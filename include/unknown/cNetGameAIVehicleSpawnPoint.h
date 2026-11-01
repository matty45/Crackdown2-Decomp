#include "rws/attributes.h"
// unknown::cNetGameAIVehicleSpawnPoint (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8284D490) builds cClass(0x489D, "cNetGameAIVehicleSpawnPoint", 0xB0); 0xB0 is the size its registrar gives.
#ifndef UNKNOWN_CNETGAMEAIVEHICLESPAWNPOINT_H
#define UNKNOWN_CNETGAMEAIVEHICLESPAWNPOINT_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cNetGameAIVehicleSpawnPoint
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcNetGameAIVehicleSpawnPointClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CNETGAMEAIVEHICLESPAWNPOINT_H
