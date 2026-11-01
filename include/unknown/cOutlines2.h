#include "rws/attributes.h"
// unknown::cOutlines2 (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x827A4090) builds cClass(0x1027FB, "cOutlines2", 0x7C); 0x7C is the size its registrar gives.
#ifndef UNKNOWN_COUTLINES2_H
#define UNKNOWN_COUTLINES2_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cOutlines2
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcOutlines2Class;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_COUTLINES2_H
