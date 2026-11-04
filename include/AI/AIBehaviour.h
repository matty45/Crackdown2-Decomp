#include "cd2/layout.h"
#include "gom/object_prototype.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
// AI::AIBehaviour (Crackdown 2): STAND-IN for the class name only. Base cNonGameBase, as in RuffKing's header;
// RetClassName (0x824A4A80) is slot 11 of the vtable at 0x82107B90, as cNonGameBase's RetClassName.
#ifndef AI_AIBEHAVIOUR_H
#define AI_AIBEHAVIOUR_H

#include "gom/non_game_base.h"

namespace AI
{
    class AIBehaviour : public cNonGameBase
    {
    public:
        // CD2 MakeNew (0x824a4a10) allocates 0x70 bytes, calls GOM::cObjectPrototype's constructor (0x82654118) with the packet and
        // installs this prototype's vtables (at 0 and 0x18).
        class AIBehaviourPrototype : public GOM::cObjectPrototype
        {
        public:
            // __forceinline: CD2 inlines this constructor into MakeNew (docs/matching-notes.md, "Inlining").
            __forceinline AIBehaviourPrototype(const RWS::CAttributePacket &packet) : GOM::cObjectPrototype(packet) {}

            CD2_LAYOUT_CHECKS(AIBehaviourPrototype, CD2_SIZE(AIBehaviourPrototype, 0x70))
        };

        // CD2 0x824A4B18 creates the named runtime descriptor.
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif // AI_AIBEHAVIOUR_H
