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
        virtual const char *RetClassName() const;
    };
}

#endif // PROP_CSLIDINGDOOR_H
