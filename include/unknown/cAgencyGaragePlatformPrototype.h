// STAND-IN: descriptive prototype name is ours; CD2 factory/constructor installs
// table 0x8213E71C after calling the shared base prototype constructor 0x8273CBD0.
// Slot 5 names the inherited CAttributeHandler::Init interface (0x82736688).
// Interface only: complete storage is unrecovered; do not use this declaration for allocation.
#ifndef CD2_UNKNOWN_CAGENCYGARAGEPLATFORMPROTOTYPE_H
#define CD2_UNKNOWN_CAGENCYGARAGEPLATFORMPROTOTYPE_H
#include "Prop/cPrismaticProp.h"
namespace unknown
{
    class cAgencyGaragePlatformPrototype : public Prop::cPrismaticProp::cPrismaticPropPrototype
    {
    public:
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
    };
}
#endif
