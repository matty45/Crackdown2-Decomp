// STAND-IN: RuffKing's cPintleFaceplatePrototype derives from cPropPrototype and adds no fields.
// CD2 MakeNew (0x82745188) confirms size 0x4F0 and base constructor 0x8272D390.
#ifndef PROP_CPINTLEFACEPLATEPROTOTYPE_H
#define PROP_CPINTLEFACEPLATEPROTOTYPE_H

#include "Prop/cProp.h"
#include "fun_runtime/retval.h"

namespace Prop
{
    class cPintleFaceplatePrototype : public cProp::cPropPrototype
    {
    public:
        cPintleFaceplatePrototype(const RWS::CAttributePacket &packet) : cPropPrototype(packet) {}
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        virtual void HandleAttributes(const RWS::CAttributePacket &);

        CD2_LAYOUT_CHECKS(cPintleFaceplatePrototype,
            CD2_SIZE(cPintleFaceplatePrototype, 0x4F0))
    };
}

#endif
