// Prop::cMovingPlatform (Crackdown 2): STAND-IN for the class name only. Base Prop::cProp, as in RuffKing's header;
// RetClassName (0x8273A838) is slot 11 of the vtable at 0x8213F800, as cNonGameBase's RetClassName.
#ifndef PROP_CMOVINGPLATFORM_H
#define PROP_CMOVINGPLATFORM_H

#include "Prop/cProp.h"

namespace Prop
{
    class cMovingPlatform : public Prop::cProp
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcMovingPlatformClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // PROP_CMOVINGPLATFORM_H
