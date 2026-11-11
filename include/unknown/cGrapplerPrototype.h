// STAND-IN: descriptive prototype name is ours; CD2 factory/constructor installs
// table 0x821291C8 after calling the shared base prototype constructor 0x82608930.
// Slot 5 names the inherited CAttributeHandler::Init interface (0x82631B30).
// MakeNew (0x82631AA8) allocates 0x3E0 bytes, confirming the derived prototype adds no storage.
#ifndef CD2_UNKNOWN_CGRAPPLERPROTOTYPE_H
#define CD2_UNKNOWN_CGRAPPLERPROTOTYPE_H
#include "Equip/cCWWeapon.h"
namespace unknown
{
    class cGrapplerPrototype : public Equip::cCWWeapon::cCWWeaponPrototype
    {
    public:
        // CD2 MakeNew calls this out of line; allocation is the unchanged 0x3E0-byte base size.
        cGrapplerPrototype(const RWS::CAttributePacket &);
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cGrapplerPrototype, CD2_SIZE(cGrapplerPrototype, 0x3E0))
    };
}
#endif
