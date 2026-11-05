#include "gom/object_prototype.h"
// AI::TrainingDummy (Crackdown 2): STAND-IN. Base NPCBehaviour (factory 0x824C82D8 calls its constructor); fields from RuffKing (0x100-0x109 there), at 0xC0-0xC9 in CD2.
#ifndef AI_TRAININGDUMMY_H
#define AI_TRAININGDUMMY_H

#include "AI/NPCBehaviour.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class TrainingDummy : public NPCBehaviour
    {
    public:
        // CD2 spawning initializer 0x82F98870 names placement factory 0x824c82d8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pTrainingDummyClass;

        // CD2's placement factory 0x824C82D8 inlines this constructor: NPCBehaviour's constructor (0x824A89C8), the vtables,
        // then the fields below. __forceinline: /Ob1 declines a plain inline constructor with this many stores
        // (docs/matching-notes.md, Inlining).
        __forceinline TrainingDummy() : m_nState(0), m_nEmoteTime(0), m_nDamageFlags(0), m_nSpawnAction(0) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

    protected:
        int m_nState; // RuffKing: TrainingDummy::eState
        unsigned int m_nEmoteTime;
        unsigned char m_nDamageFlags;
        unsigned char m_nSpawnAction;

        CD2_LAYOUT_CHECKS(TrainingDummy,
            CD2_SIZE(TrainingDummy, 0xD0)
            CD2_OFFSET(TrainingDummy, m_nState, 0xC0)
            CD2_OFFSET(TrainingDummy, m_nEmoteTime, 0xC4)
            CD2_OFFSET(TrainingDummy, m_nDamageFlags, 0xC8)
            CD2_OFFSET(TrainingDummy, m_nSpawnAction, 0xC9))
    };
}

#endif

