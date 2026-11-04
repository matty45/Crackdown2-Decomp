#include "rws/attributes.h"
// Equip::cMag (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8260BC88) builds cClass(0x27411, "cMag", 0xB20); 0xB20 is the size its registrar gives.
#ifndef EQUIP_CMAG_H
#define EQUIP_CMAG_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cMag
    {
    public:
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcMagClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CMAG_H
