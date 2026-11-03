// STAND-IN: RuffKing's name, base and radio-station member. CD2 MakeNew (0x82742D68)
// confirms the word at 0x4F0 and 0x500-byte allocation, including the prototype's alignment.
#ifndef PROP_CBOOMBOXPROTOTYPE_H
#define PROP_CBOOMBOXPROTOTYPE_H

#include "Prop/cProp.h"

namespace Prop
{
    __declspec(align(16)) class cBoomBoxPrototype : public cProp::cPropPrototype
    {
    public:
        cBoomBoxPrototype(const RWS::CAttributePacket &packet) : cPropPrototype(packet), m_nRadioStation(0) {}
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        int m_nRadioStation;

        CD2_LAYOUT_CHECKS(cBoomBoxPrototype,
            CD2_SIZE(cBoomBoxPrototype, 0x500)
            CD2_OFFSET(cBoomBoxPrototype, m_nRadioStation, 0x4F0))
    };
}

#endif
