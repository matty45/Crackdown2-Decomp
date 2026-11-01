#include "rws/attributes.h"
// unknown::cPhantomBody (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8268A408) builds cClass(0x7, "cPhantomBody", 0x140); 0x140 is the size its registrar gives.
#ifndef UNKNOWN_CPHANTOMBODY_H
#define UNKNOWN_CPHANTOMBODY_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cPhantomBody
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcPhantomBodyClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CPHANTOMBODY_H
