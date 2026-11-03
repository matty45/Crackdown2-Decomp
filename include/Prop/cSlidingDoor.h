#include "fun_runtime/class.h"
#include "rws/attributes.h"
// Prop::cSlidingDoor (Crackdown 2): STAND-IN for the class name only. Base Prop::cPrismaticProp, as in RuffKing's
// header; RetClassName (0x82746958) is slot 11 of the vtable at 0x82011C50, as cNonGameBase's RetClassName.
#ifndef PROP_CSLIDINGDOOR_H
#define PROP_CSLIDINGDOOR_H

#include "Prop/cPrismaticProp.h"

namespace Prop
{
    class cSlidingDoor : public Prop::cPrismaticProp
    {
    public:
        // CD2 0x82746988 creates the named runtime descriptor.
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif // PROP_CSLIDINGDOOR_H
