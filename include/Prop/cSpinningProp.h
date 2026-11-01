// Prop::cSpinningProp (Crackdown 2): STAND-IN for the class name only. Base Prop::cPivotBasedProp, as in RuffKing's
// header; RetClassName (0x8273E670) is slot 11 of the vtable at 0x82141860, as cNonGameBase's RetClassName.
#ifndef PROP_CSPINNINGPROP_H
#define PROP_CSPINNINGPROP_H

#include "Prop/cPivotBasedProp.h"

namespace Prop
{
    class cSpinningProp : public Prop::cPivotBasedProp
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcSpinningPropClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // PROP_CSPINNINGPROP_H
