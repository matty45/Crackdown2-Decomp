// Prop::cHingedProp (Crackdown 2): STAND-IN for the class name only. Base Prop::cPivotBasedProp, as in RuffKing's
// header; RetClassName (0x82736E40) is slot 11 of the vtable at 0x8213E830, as cNonGameBase's RetClassName.
#ifndef PROP_CHINGEDPROP_H
#define PROP_CHINGEDPROP_H

#include "Prop/cPivotBasedProp.h"

namespace Prop
{
    class cHingedProp : public Prop::cPivotBasedProp
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcHingedPropClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // PROP_CHINGEDPROP_H
