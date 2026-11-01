// unknown::cSupplyEntryPoint (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8273FC98) builds cClass(0x101F, "cSupplyEntryPoint", 0x140); 0x140 is the size its registrar gives.
#ifndef UNKNOWN_CSUPPLYENTRYPOINT_H
#define UNKNOWN_CSUPPLYENTRYPOINT_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cSupplyEntryPoint
    {
    public:
        static const Fun_Runtime::cClass *ms_pcSupplyEntryPointClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CSUPPLYENTRYPOINT_H
