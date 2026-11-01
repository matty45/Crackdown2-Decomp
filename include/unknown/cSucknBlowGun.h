#include "rws/attributes.h"
// unknown::cSucknBlowGun (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82635588) builds cClass(0x27418, "cSucknBlowGun", 0xDF0); 0xDF0 is the size its registrar gives.
#ifndef UNKNOWN_CSUCKNBLOWGUN_H
#define UNKNOWN_CSUCKNBLOWGUN_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cSucknBlowGun
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcSucknBlowGunClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CSUCKNBLOWGUN_H
