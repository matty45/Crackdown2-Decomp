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
        // CD2 placement factory 0x8273A848; constructor signature follows RuffKing.
        cMovingPlatform(GOM::cObjectPrototype *);
        // CD2 destructor 0x8273AA30 only restores the vtables and calls cProp's destructor.
        virtual ~cMovingPlatform();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcMovingPlatformClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // PROP_CMOVINGPLATFORM_H
