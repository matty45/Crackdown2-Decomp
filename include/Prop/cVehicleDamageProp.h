#include "rws/attributes.h"
// Prop::cVehicleDamageProp (Crackdown 2): STAND-IN for the class name only. Base Prop::cProp, as in RuffKing's header;
// RetClassName (0x82731E10) is slot 11 of the vtable at 0x82011120, as cNonGameBase's RetClassName.
#ifndef PROP_CVEHICLEDAMAGEPROP_H
#define PROP_CVEHICLEDAMAGEPROP_H

#include "Prop/cProp.h"

namespace Prop
{
    class cVehicleDamageProp : public Prop::cProp
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif // PROP_CVEHICLEDAMAGEPROP_H
