#include "cd2/layout.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// AI::cBeaconProp (Crackdown 2): STAND-IN for the class name only. Base AI::cMissionCriticalProp, as in RuffKing's
// header; RetClassName (0x8245C278) is slot 11 of the vtable at 0x82103748, as cNonGameBase's RetClassName.
#ifndef AI_CBEACONPROP_H
#define AI_CBEACONPROP_H

#include "AI/cMissionCriticalProp.h"

namespace AI
{
    class cBeaconProp : public AI::cMissionCriticalProp
    {
    public:
        // CD2 MakeNew (0x8245C200) allocates 0x500 bytes and builds cMissionCriticalProp's prototype with the packet
        // (cPropPrototype's constructor 0x8272D390, then the word at 0x4F0 = 0) before installing these vtables.
        class cBeaconPropPrototype : public AI::cMissionCriticalProp::cMissionCriticalPropPrototype
        {
        public:
            // __forceinline: CD2 inlines this constructor into MakeNew (docs/matching-notes.md, "Inlining").
            __forceinline cBeaconPropPrototype(const RWS::CAttributePacket &packet)
                : AI::cMissionCriticalProp::cMissionCriticalPropPrototype(packet) {}

            CD2_LAYOUT_CHECKS(cBeaconPropPrototype, CD2_SIZE(cBeaconPropPrototype, 0x500))
        };

        // Out of line: CD2 tail-calls it from SpawnFromPrototype with the prototype.
        cBeaconProp(GOM::cObjectPrototype *prototype);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcBeaconPropClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // AI_CBEACONPROP_H
