#include "cd2/layout.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// AI::cMissionCriticalProp (Crackdown 2): STAND-IN for the class name only. Base Prop::cProp, as in RuffKing's header;
// RetClassName (0x8245AF38) is slot 11 of the vtable at 0x82102F88, as cNonGameBase's RetClassName.
#ifndef AI_CMISSIONCRITICALPROP_H
#define AI_CMISSIONCRITICALPROP_H

#include "Prop/cProp.h"

namespace AI
{
    class cMissionCriticalProp : public Prop::cProp
    {
    public:
        // CD2 MakeNew (0x8245AEC0) allocates 0x500 bytes, calls Prop::cProp::cPropPrototype's constructor with the packet, installs
        // this prototype's vtables (at 0 and 0x18) and initialises the fields below (names ours).
        class cMissionCriticalPropPrototype : public Prop::cProp::cPropPrototype
        {
        public:
            // __forceinline: CD2 inlines this constructor into MakeNew (docs/matching-notes.md, "Inlining").
            __forceinline cMissionCriticalPropPrototype(const RWS::CAttributePacket &packet)
                : Prop::cProp::cPropPrototype(packet), m_nUnknown4F0(0) {}

        private:
            unsigned int m_nUnknown4F0; // 0x4F0
            unsigned char m_pad4F4[0x500 - 0x4F4];

            CD2_LAYOUT_CHECKS(cMissionCriticalPropPrototype,
                CD2_SIZE(cMissionCriticalPropPrototype, 0x500)
                CD2_OFFSET(cMissionCriticalPropPrototype, m_nUnknown4F0, 0x4F0))
        };

        // Out of line: CD2 tail-calls it from SpawnFromPrototype with the prototype.
        cMissionCriticalProp(GOM::cObjectPrototype *prototype);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcMissionCriticalPropClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // AI_CMISSIONCRITICALPROP_H
