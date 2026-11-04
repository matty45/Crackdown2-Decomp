// STAND-IN: descriptive prototype name is ours; CD2 factory/constructor installs
// table 0x821291C8 after calling the shared base prototype constructor 0x82608930.
// Slot 5 names the inherited CAttributeHandler::Init interface (0x82631B30).
// Interface only: complete storage is unrecovered; do not use this declaration for allocation.
#ifndef CD2_UNKNOWN_CGRAPPLERPROTOTYPE_H
#define CD2_UNKNOWN_CGRAPPLERPROTOTYPE_H
#include "Equip/cCWWeapon.h"
namespace unknown
{
    class cGrapplerPrototype : public Equip::cCWWeapon::cCWWeaponPrototype
    {
    public:
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
    };
}
#endif
