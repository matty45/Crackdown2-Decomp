// Prop::cPrismaticProp (Crackdown 2): STAND-IN for the class name only. Base Prop::cPivotBasedProp, as in RuffKing's
// header; RetClassName (0x8273B5A0) is slot 11 of the vtable at 0x821405E8, as cNonGameBase's RetClassName.
#ifndef PROP_CPRISMATICPROP_H
#define PROP_CPRISMATICPROP_H

#include "Prop/cPivotBasedProp.h"

namespace Prop
{
    class cPrismaticProp : public Prop::cPivotBasedProp
    {
    public:
        static const Fun_Runtime::cClass *ms_pcPrismaticPropClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // PROP_CPRISMATICPROP_H
