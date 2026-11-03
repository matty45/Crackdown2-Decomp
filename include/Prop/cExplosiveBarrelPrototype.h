// STAND-IN: RuffKing name/base/fields; CD2 MakeNew (0x827430C8) allocates 0x500,
// sets the two millisecond durations at 0x4F0/0x4F4 to 3000/1000, and installs the vtable.
#ifndef PROP_CEXPLOSIVEBARRELPROTOTYPE_H
#define PROP_CEXPLOSIVEBARRELPROTOTYPE_H

#include "Prop/cProp.h"
#include "fun_runtime/retval.h"

namespace Prop
{
    __declspec(align(16)) class cExplosiveBarrelPrototype : public cProp::cPropPrototype
    {
    public:
        cExplosiveBarrelPrototype(const RWS::CAttributePacket &packet)
            : cPropPrototype(packet), m_nBarrelDeleteDelay(3000), m_nBarrelFadeDuration(1000) {}
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        unsigned int m_nBarrelDeleteDelay;
        unsigned int m_nBarrelFadeDuration;

        CD2_LAYOUT_CHECKS(cExplosiveBarrelPrototype,
            CD2_SIZE(cExplosiveBarrelPrototype, 0x500)
            CD2_OFFSET(cExplosiveBarrelPrototype, m_nBarrelDeleteDelay, 0x4F0)
            CD2_OFFSET(cExplosiveBarrelPrototype, m_nBarrelFadeDuration, 0x4F4))
    };
}

#endif
