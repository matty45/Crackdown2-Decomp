#include "rws/attributes.h"
// Equip::cCloakingDevice (Crackdown 2): STAND-IN with only what its matched functions need; its bases are not modelled yet.
// Its class-factory registrar (0x82FCC720) registers "cCloakingDevice" with MakeNew (0x8260B1E8) and size 0x9C0.
#ifndef EQUIP_CCLOAKINGDEVICE_H
#define EQUIP_CCLOAKINGDEVICE_H

namespace Equip
{
    class cCloakingDevice
    {
    public:
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // EQUIP_CCLOAKINGDEVICE_H
