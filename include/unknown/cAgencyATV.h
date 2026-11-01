// unknown::cAgencyATV (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x826E3300) builds cClass(0x12065, "cAgencyATV", 0x31F0); 0x31F0 is the size its registrar gives.
#ifndef UNKNOWN_CAGENCYATV_H
#define UNKNOWN_CAGENCYATV_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cAgencyATV
    {
    public:
        static const Fun_Runtime::cClass *ms_pcAgencyATVClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CAGENCYATV_H
