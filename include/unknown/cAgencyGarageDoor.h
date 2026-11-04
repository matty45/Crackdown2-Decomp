#ifndef unknown_cAgencyGarageDoor_H
#define unknown_cAgencyGarageDoor_H

#include "cd2/layout.h"
#include "Prop/cSlidingDoor.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace unknown
{
    class cAgencyGarageDoor : public RWS::CAttributeHandler
    {
    public:
        // CD2 MakeNew (0x82732DC0) allocates 0x540 bytes, calls Prop::cSlidingDoor::cSlidingDoorPrototype's constructor with the packet, installs
        // this prototype's vtables (at 0 and 0x18) and initialises the fields below (names ours).
        class cAgencyGarageDoorPrototype : public Prop::cSlidingDoor::cSlidingDoorPrototype
        {
        public:
            // __forceinline: CD2 inlines this constructor into MakeNew (docs/matching-notes.md, "Inlining").
            __forceinline cAgencyGarageDoorPrototype(const RWS::CAttributePacket &packet)
                : Prop::cSlidingDoor::cSlidingDoorPrototype(packet), m_nUnknown530(-1) {}

        private:
            int m_nUnknown530; // 0x530
            unsigned char m_pad534[0x540 - 0x534];

            CD2_LAYOUT_CHECKS(cAgencyGarageDoorPrototype,
                CD2_SIZE(cAgencyGarageDoorPrototype, 0x540)
                CD2_OFFSET(cAgencyGarageDoorPrototype, m_nUnknown530, 0x530))
        };

        // Out of line: CD2 tail-calls it from SpawnFromPrototype with the prototype.
        cAgencyGarageDoor(GOM::cObjectPrototype *prototype);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static const Fun_Runtime::cClass *ms_pcAgencyGarageDoorClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
