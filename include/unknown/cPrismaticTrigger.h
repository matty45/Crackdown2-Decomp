#include "rws/attributes.h"
// unknown::cPrismaticTrigger (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8273D510) builds cClass(0xCB57, "cPrismaticTrigger", 0x160); 0x160 is the size its registrar gives.
#ifndef UNKNOWN_CPRISMATICTRIGGER_H
#define UNKNOWN_CPRISMATICTRIGGER_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cPrismaticTrigger
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcPrismaticTriggerClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CPRISMATICTRIGGER_H
