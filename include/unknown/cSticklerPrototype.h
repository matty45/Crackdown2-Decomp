// STAND-IN: descriptive prototype name is ours; CD2's factory (0x82622E58) allocates 0x430, calls
// cCWSatchelChargePrototype's constructor (0x8261CA88) and installs table 0x82125F20: the constructor is inline and
// adds no fields. Slot 5 names the inherited CAttributeHandler::Init interface (0x82622FA0).
#ifndef CD2_UNKNOWN_CSTICKLERPROTOTYPE_H
#define CD2_UNKNOWN_CSTICKLERPROTOTYPE_H
#include "Equip/cCWSatchelCharge.h"
namespace unknown
{
    class cSticklerPrototype : public Equip::cCWSatchelCharge::cCWSatchelChargePrototype
    {
    public:
        __forceinline cSticklerPrototype(const RWS::CAttributePacket &packet)
            : Equip::cCWSatchelCharge::cCWSatchelChargePrototype(packet) {}
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);

        CD2_LAYOUT_CHECKS(cSticklerPrototype,
            CD2_SIZE(cSticklerPrototype, 0x430))
    };
}
#endif
