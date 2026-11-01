// Prop::cPivotBasedProp (Crackdown 2): STAND-IN for the class name only. Base Prop::cProp, as in RuffKing's header;
// RetClassName (0x8273AED8) is slot 11 of the vtable at 0x8213FEB8, as cNonGameBase's RetClassName.
#ifndef PROP_CPIVOTBASEDPROP_H
#define PROP_CPIVOTBASEDPROP_H

#include "Prop/cProp.h"

namespace Prop
{
    class cPivotBasedProp : public Prop::cProp
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcPivotBasedPropClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // PROP_CPIVOTBASEDPROP_H
