// STAND-IN: descriptive prototype name is ours; CD2 factory/constructor installs
// table 0x8213E71C after calling the shared base prototype constructor 0x8273CBD0.
// Slot 5 names the inherited CAttributeHandler::Init interface (0x82736688).
// Interface only: complete storage is unrecovered; do not use this declaration for allocation.
#ifndef CD2_UNKNOWN_CAGENCYGARAGEPLATFORMPROTOTYPE_H
#define CD2_UNKNOWN_CAGENCYGARAGEPLATFORMPROTOTYPE_H
#include "Prop/cPrismaticProp.h"
namespace unknown
{
    // CD2's MakeNew (0x82736250) allocates 0x530, calls cPrismaticPropPrototype's constructor (0x8273CBD0) and stores
    // this class's vptrs: the constructor is inline and adds no fields.
    class cAgencyGaragePlatformPrototype : public Prop::cPrismaticProp::cPrismaticPropPrototype
    {
    public:
        __forceinline cAgencyGaragePlatformPrototype(const RWS::CAttributePacket &packet)
            : Prop::cPrismaticProp::cPrismaticPropPrototype(packet) {}
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);

        CD2_LAYOUT_CHECKS(cAgencyGaragePlatformPrototype,
            CD2_SIZE(cAgencyGaragePlatformPrototype, 0x530))
    };
}
#endif
