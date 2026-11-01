#include "rws/attributes.h"
// unknown::cPopulationZone (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8280C090) builds cClass(0x416, "cPopulationZone", 0x150); 0x150 is the size its registrar gives.
#ifndef UNKNOWN_CPOPULATIONZONE_H
#define UNKNOWN_CPOPULATIONZONE_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cPopulationZone
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcPopulationZoneClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CPOPULATIONZONE_H
