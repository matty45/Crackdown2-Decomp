// unknown::cSpawnPortal (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8273E150) builds cClass(0x1025, "cSpawnPortal", 0xEC0); 0xEC0 is the size its registrar gives.
#ifndef UNKNOWN_CSPAWNPORTAL_H
#define UNKNOWN_CSPAWNPORTAL_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cSpawnPortal
    {
    public:
        static const Fun_Runtime::cClass *ms_pcSpawnPortalClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CSPAWNPORTAL_H
