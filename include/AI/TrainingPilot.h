#include "gom/object_prototype.h"
// AI::TrainingPilot (Crackdown 2): STAND-IN. Base NPCBehaviour (inheritance registrar; factory 0x824C8DA8 calls its constructor); m_bPatrolling from RuffKing, at 0xC0 in CD2.
#ifndef AI_TRAININGPILOT_H
#define AI_TRAININGPILOT_H

#include "AI/NPCBehaviour.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class TrainingPilot : public NPCBehaviour
    {
    public:
        // CD2 spawning initializer 0x82F98CA8 names placement factory 0x824c8da8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pTrainingPilotClass;

        // CD2's placement factory 0x824C8DA8 inlines this constructor: NPCBehaviour's constructor (0x824A89C8), the vtables,
        // then the fields below. __forceinline: /Ob1 declines a plain inline constructor with this many stores
        // (docs/matching-notes.md, Inlining).
        __forceinline TrainingPilot() : m_bPatrolling(false) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

    protected:
        bool m_bPatrolling;

        CD2_LAYOUT_CHECKS(TrainingPilot,
            CD2_SIZE(TrainingPilot, 0xD0)
            CD2_OFFSET(TrainingPilot, m_bPatrolling, 0xC0))
    };
}

#endif

