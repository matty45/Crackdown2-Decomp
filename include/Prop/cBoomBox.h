#include "rws/attributes.h"
// Prop::cBoomBox (Crackdown 2): STAND-IN for the class name only. Base Prop::cProp, as in RuffKing's header;
// RetClassName (0x82742DE0) is slot 11 of the vtable at 0x8200D518, as cNonGameBase's RetClassName.
#ifndef PROP_CBOOMBOX_H
#define PROP_CBOOMBOX_H

#include "Prop/cProp.h"

namespace Prop
{
    class cBoomBox : public Prop::cProp
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif // PROP_CBOOMBOX_H
