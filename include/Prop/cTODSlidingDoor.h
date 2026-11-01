#include "rws/attributes.h"
// Prop::cTODSlidingDoor (Crackdown 2): STAND-IN for the class name only. Base Prop::cSlidingDoor, as in RuffKing's
// header; RetClassName (0x82746F70) is slot 11 of the vtable at 0x82012230, as cNonGameBase's RetClassName.
#ifndef PROP_CTODSLIDINGDOOR_H
#define PROP_CTODSLIDINGDOOR_H

#include "Prop/cSlidingDoor.h"

namespace Prop
{
    class cTODSlidingDoor : public Prop::cSlidingDoor
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcTODSlidingDoorClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // PROP_CTODSLIDINGDOOR_H
