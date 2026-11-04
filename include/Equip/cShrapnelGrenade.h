#include "rws/attributes.h"
// Equip::cShrapnelGrenade (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82621C20) builds cClass(0x3E8C, "cShrapnelGrenade", 0x9D0); 0x9D0 is the size its registrar gives.
#ifndef EQUIP_CSHRAPNELGRENADE_H
#define EQUIP_CSHRAPNELGRENADE_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cShrapnelGrenade
    {
    public:
        virtual const char *RetClassName() const;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcShrapnelGrenadeClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CSHRAPNELGRENADE_H
