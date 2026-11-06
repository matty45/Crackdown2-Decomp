// STAND-IN: descriptive prototype name is ours; CD2's MakeNew (0x826354F0) allocates 0x4B0 and calls its constructor
// (0x82639B18), which calls cCWWeaponPrototype's (0x82608930) and installs table 0x8212A1A8. Own fields are not
// recovered. Slot 5 names the inherited CAttributeHandler::Init interface (0x82635570).
#ifndef CD2_UNKNOWN_CSUCKNBLOWGUNPROTOTYPE_H
#define CD2_UNKNOWN_CSUCKNBLOWGUNPROTOTYPE_H
#include "Equip/cCWWeapon.h"
namespace unknown
{
    class cSucknBlowGunPrototype : public Equip::cCWWeapon::cCWWeaponPrototype
    {
    public:
        cSucknBlowGunPrototype(const RWS::CAttributePacket &);
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);

    private:
        unsigned char m_unmodelled3E0[0x4B0 - 0x3E0];

        CD2_LAYOUT_CHECKS(cSucknBlowGunPrototype,
            CD2_SIZE(cSucknBlowGunPrototype, 0x4B0))
    };
}
#endif
