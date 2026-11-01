#include "rws/attributes.h"
// Prop::cGasCanister (Crackdown 2): STAND-IN for the class name only. Base Prop::cProp, as in RuffKing's header;
// RetClassName (0x827437F8) is slot 11 of the vtable at 0x8200E520, as cNonGameBase's RetClassName.
#ifndef PROP_CGASCANISTER_H
#define PROP_CGASCANISTER_H

#include "Prop/cProp.h"

namespace Prop
{
    class cGasCanister : public Prop::cProp
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif // PROP_CGASCANISTER_H
