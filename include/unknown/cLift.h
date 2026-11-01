// unknown::cLift (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82738F88) builds cClass(0x102B, "cLift", 0xF30); 0xF30 is the size its registrar gives.
#ifndef UNKNOWN_CLIFT_H
#define UNKNOWN_CLIFT_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cLift
    {
    public:
        static const Fun_Runtime::cClass *ms_pcLiftClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CLIFT_H
