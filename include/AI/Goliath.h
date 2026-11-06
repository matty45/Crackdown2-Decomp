#include "gom/object_prototype.h"
#include "rws/attributes.h"
// AI::Goliath (Crackdown 2): STAND-IN for the class name only. Base AI::NPCBehaviourSM, as in RuffKing's header;
// RetClassName (0x824B0F18) is slot 11 of the vtable at 0x821096A0, as cNonGameBase's RetClassName.
#ifndef AI_GOLIATH_H
#define AI_GOLIATH_H

#include "AI/cChaseBehaviour.h"

namespace AI
{
    // RuffKing: AI::GoliathPrototype : NPCBehaviourPrototype, 144 bytes. CD2's Goliath::MakeNew (0x824B0EA8) allocates
    // 0x90, calls NPCBehaviourPrototype's constructor (0x824A8608) and stores this class's vptrs; its table
    // (0x82109670) overrides slot 1 with 0x824B2560.
    class GoliathPrototype : public NPCBehaviourPrototype
    {
    public:
        __forceinline GoliathPrototype(const RWS::CAttributePacket &packet) : NPCBehaviourPrototype(packet) {}
        virtual void HandleAttributes(const RWS::CAttributePacket &);

        CD2_LAYOUT_CHECKS(GoliathPrototype,
            CD2_SIZE(GoliathPrototype, 0x90))
    };

    class Goliath : public AI::NPCBehaviourSM
    {
    public:
        // CD2 spawning initializer 0x82F93B58 names placement factory 0x824b0f28.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pGoliathClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // AI_GOLIATH_H
