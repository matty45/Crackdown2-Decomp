#include "cd2/layout.h"
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
        // RuffKing signature; CD2's placement factory tail-calls 0x82746A78.
        cSlidingDoor(GOM::cObjectPrototype *);
        static const Fun_Runtime::cClass *ms_pcSlidingDoorClass;
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 MakeNew (0x827468e8) allocates 0x530 bytes, calls Prop::cPrismaticProp::cPrismaticPropPrototype's constructor (0x8273CBD0) with the packet and
        // installs this prototype's vtables (at 0 and 0x18).
        class cSlidingDoorPrototype : public Prop::cPrismaticProp::cPrismaticPropPrototype
        {
        public:
            // __forceinline: CD2 inlines this constructor into MakeNew (docs/matching-notes.md, "Inlining").
            __forceinline cSlidingDoorPrototype(const RWS::CAttributePacket &packet) : Prop::cPrismaticProp::cPrismaticPropPrototype(packet) {}

            // CD2: cSlidingDoorPrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
            // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
        public:
            virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x8273CC70
            virtual Fun_Runtime::RetVal Init(RWS::CAttributePacket const &); // 5: 0x82746D80
        public:
            CD2_LAYOUT_CHECKS(cSlidingDoorPrototype, CD2_SIZE(cSlidingDoorPrototype, 0x530))
        };

        // CD2 0x82746988 creates the named runtime descriptor.
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        // CD2 0x82746B78 (out of line: cAgencyGarageDoor's destructor calls it).
        virtual ~cSlidingDoor();
    };
}

#endif // PROP_CSLIDINGDOOR_H
