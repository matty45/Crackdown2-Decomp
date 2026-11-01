// unknown::cTeleporterDoor (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82740A58) builds cClass(0x1022, "cTeleporterDoor", 0xEF0); 0xEF0 is the size its registrar gives.
#ifndef UNKNOWN_CTELEPORTERDOOR_H
#define UNKNOWN_CTELEPORTERDOOR_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cTeleporterDoor
    {
    public:
        static const Fun_Runtime::cClass *ms_pcTeleporterDoorClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CTELEPORTERDOOR_H
