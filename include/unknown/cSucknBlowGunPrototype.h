// STAND-IN: descriptive prototype name is ours; CD2 factory/constructor installs
// table 0x8212A1A8 after calling the shared base prototype constructor 0x82608930.
// Slot 5 names the inherited CAttributeHandler::Init interface (0x82635570).
// Interface only: complete storage is unrecovered; do not use this declaration for allocation.
#ifndef CD2_UNKNOWN_CSUCKNBLOWGUNPROTOTYPE_H
#define CD2_UNKNOWN_CSUCKNBLOWGUNPROTOTYPE_H
#include "Equip/cCWWeapon.h"
namespace unknown
{
    class cSucknBlowGunPrototype : public Equip::cCWWeapon::cCWWeaponPrototype
    {
    public:
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
    };
}
#endif
