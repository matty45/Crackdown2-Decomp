#include "fun_runtime/class.h"
#include "rws/attributes.h"
// Equip::cExplosiveGrenade (Crackdown 2): STAND-IN with only what its matched functions need; its bases are not modelled yet.
// Its class-factory registrar (0x82FCFAA8) registers "cExplosiveGrenade" with MakeNew (0x8261D1B8) and size 0x9D0.
#ifndef EQUIP_CEXPLOSIVEGRENADE_H
#define EQUIP_CEXPLOSIVEGRENADE_H

namespace Equip
{
    class cExplosiveGrenade
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // EQUIP_CEXPLOSIVEGRENADE_H
