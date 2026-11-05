#include "gom/object_prototype.h"
// AI::TrainingAmbient (Crackdown 2): STAND-IN. Bases from RuffKing (NPCBehaviour's constructor is called by factory 0x824C7C60); fields from RuffKing, at 0xC0/0xC4 in CD2.
#ifndef AI_TRAININGAMBIENT_H
#define AI_TRAININGAMBIENT_H

#include "AI/NPCBehaviour.h"
#include "AI/cNPCArmourySetup.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace Activity
{
    class cSquadMemberSpawnPoint;
}

namespace AI
{
    class TrainingAmbient : public NPCBehaviour, public cNPCArmourySetup
    {
    public:
        // CD2 spawning initializer 0x82F98438 names placement factory 0x824c7c60.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pTrainingAmbientClass;

        // CD2's placement factory 0x824C7C60 inlines this constructor: NPCBehaviour's constructor (0x824A89C8), the vtables,
        // then the fields below. __forceinline: /Ob1 declines a plain inline constructor with this many stores
        // (docs/matching-notes.md, Inlining).
        __forceinline TrainingAmbient() : m_pTargetSP(0), m_nState(0) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

    protected:
        Activity::cSquadMemberSpawnPoint *m_pTargetSP;
        int m_nState; // RuffKing: TrainingAmbient::eState

        CD2_LAYOUT_CHECKS(TrainingAmbient,
            CD2_SIZE(TrainingAmbient, 0xD0)
            CD2_OFFSET(TrainingAmbient, m_pTargetSP, 0xC0)
            CD2_OFFSET(TrainingAmbient, m_nState, 0xC4))
    };
}

#endif

