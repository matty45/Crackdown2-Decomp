#include "rws/attributes.h"
// Prop::cExplosiveBarrel (Crackdown 2): STAND-IN for the class name only. Base Prop::cProp, as in RuffKing's header;
// RetClassName (0x82743148) is slot 11 of the vtable at 0x8200DA70, as cNonGameBase's RetClassName.
#ifndef PROP_CEXPLOSIVEBARREL_H
#define PROP_CEXPLOSIVEBARREL_H

#include "Prop/cProp.h"

namespace Prop
{
    class cExplosiveBarrel : public Prop::cProp
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif // PROP_CEXPLOSIVEBARREL_H
