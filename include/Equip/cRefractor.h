#include "rws/attributes.h"
// Equip::cRefractor (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82610758) builds cClass(0x27415, "cRefractor", 0xA60); 0xA60 is the size its registrar gives.
#ifndef EQUIP_CREFRACTOR_H
#define EQUIP_CREFRACTOR_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cRefractor
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcRefractorClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CREFRACTOR_H
