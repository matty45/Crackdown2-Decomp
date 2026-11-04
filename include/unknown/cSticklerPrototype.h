// STAND-IN: descriptive prototype name is ours; CD2 factory/constructor installs
// table 0x82125F20 after calling the shared base prototype constructor 0x8261CA88.
// Slot 5 names the inherited CAttributeHandler::Init interface (0x82622FA0).
// Interface only: complete storage is unrecovered; do not use this declaration for allocation.
#ifndef CD2_UNKNOWN_CSTICKLERPROTOTYPE_H
#define CD2_UNKNOWN_CSTICKLERPROTOTYPE_H
#include "Equip/cGrenade.h"
namespace unknown
{
    class cSticklerPrototype : public Equip::cGrenade::cGrenadePrototype
    {
    public:
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
    };
}
#endif
