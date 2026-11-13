// STAND-IN: descriptive type name and field names are ours. CD2 factory 0x8260ABB0
// allocates 0x390 bytes and calls cGrenadePrototype's constructor (0x8261F758).
// Its stores and getters 0x8260AD48..0x8260AD78 establish the fields below.
#ifndef UNKNOWN_CBOOSTPACKPROTOTYPE_H
#define UNKNOWN_CBOOSTPACKPROTOTYPE_H

#include "Equip/cGrenade.h"

namespace unknown
{
    class cBoostPackPrototype : public Equip::cGrenade::cGrenadePrototype
    {
    public:
        // CD2 inlines this initialization in factory 0x8260ABB0.
        __forceinline cBoostPackPrototype(const RWS::CAttributePacket &packet)
            : Equip::cGrenade::cGrenadePrototype(packet), m_fField370(100.0f),
              m_fField374(4.0f), m_fField378(4.0f), m_fField37C(2.0f), m_bField380(true)
        {
            m_EquipmentType = Equip::eEquipT_Secondary;
        }
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        // CD2 table 0x82120508 slot 5 points to the return-code body at 0x8260B110.
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);

        float m_fField370;
        float m_fField374;
        float m_fField378;
        float m_fField37C;
        bool m_bField380;

        CD2_LAYOUT_CHECKS(cBoostPackPrototype,
            CD2_SIZE(cBoostPackPrototype, 0x390)
            CD2_OFFSET(cBoostPackPrototype, m_fField370, 0x370)
            CD2_OFFSET(cBoostPackPrototype, m_fField374, 0x374)
            CD2_OFFSET(cBoostPackPrototype, m_fField378, 0x378)
            CD2_OFFSET(cBoostPackPrototype, m_fField37C, 0x37C)
            CD2_OFFSET(cBoostPackPrototype, m_bField380, 0x380))
    };
}

#endif
