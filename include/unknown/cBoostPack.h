// unknown::cBoostPack (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8260ADA0) builds cClass(0x10141, "cBoostPack", 0x9D0); 0x9D0 is the size its registrar gives.
#ifndef UNKNOWN_CBOOSTPACK_H
#define UNKNOWN_CBOOSTPACK_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cBoostPack
    {
    public:
        static const Fun_Runtime::cClass *ms_pcBoostPackClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CBOOSTPACK_H
