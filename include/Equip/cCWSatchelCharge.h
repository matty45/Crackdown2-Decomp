#include "fun_runtime/class.h"
#include "rws/attributes.h"
// Equip::cCWSatchelCharge (Crackdown 2): STAND-IN with only what its matched functions need; its bases are not modelled yet.
// Its class-factory registrar (0x82FCF618) registers "cCWSatchelCharge" with MakeNew (0x8261A1B8) and size 0xAE0.
#ifndef EQUIP_CCWSATCHELCHARGE_H
#define EQUIP_CCWSATCHELCHARGE_H

namespace Equip
{
    class cCWSatchelCharge
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // EQUIP_CCWSATCHELCHARGE_H
