// Prop::cSearchLight (Crackdown 2): STAND-IN for the class name only. Base Prop::cProp, as in RuffKing's header;
// RetClassName (0x82745760) is slot 11 of the vtable at 0x821441D8, as cNonGameBase's RetClassName.
#ifndef PROP_CSEARCHLIGHT_H
#define PROP_CSEARCHLIGHT_H

#include "Prop/cProp.h"

namespace Prop
{
    class cSearchLight : public Prop::cProp
    {
    public:
        // CD2 0x827459D8 only restores vtables and invokes cProp's destructor.
        virtual ~cSearchLight();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcSearchLightClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // PROP_CSEARCHLIGHT_H
