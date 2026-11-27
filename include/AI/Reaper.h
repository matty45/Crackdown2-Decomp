#include "gom/object_prototype.h"
#ifndef AI_REAPER_H
#define AI_REAPER_H

#include "gom/non_game_base.h"
#include "AI/FreakBase.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class Reaper : public FreakBase
    {
    public:
        // CD2 table 0x82109970 has 179 primary slots, as FreakBase's: Reaper's CEventHandler table (its first word the
        // adjustor thunk 0x824BAA00) starts at 0x82109C3C, 179 words on. Reaper adds no primary virtual.

        // CD2 spawning initializer 0x82F93F90 names placement factory 0x824b26a8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        // CD2 0x824B27E0, out of line: SpawnFromPrototype tail-calls it with the prototype.
        Reaper(GOM::cObjectPrototype *prototype);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pReaperClass;

        Reaper();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        // RuffKing: Reaper::ReaperPrototype : FreakPrototype, 880 bytes. CD2's MakeNew (0x824B2640) allocates 0x370 and
        // calls this constructor (0x824B80A8), which calls FreakPrototype's (0x824B0B78).
        class ReaperPrototype : public FreakPrototype
        {
        public:
            ReaperPrototype(const RWS::CAttributePacket &);

        private:
            unsigned char m_unmodelledB0[0x370 - 0xB0];

            CD2_LAYOUT_CHECKS(ReaperPrototype,
                CD2_SIZE(ReaperPrototype, 0x370))
        };

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        // CD2: Reaper's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void OnEnter(); // 68: 0x824B2A38
        virtual void OnExit(); // 69: 0x824B2C30
        virtual void Update(float fDeltaTime); // 71: 0x824B5330
        virtual void OnEnterReplicatedState(unsigned char); // 72: 0x824B2CD8
        virtual void OnCharacterEvent(unsigned char,unsigned char,unsigned char); // 80: 0x824B69F0
        virtual unsigned char GetStateReplicationInfo() const; // 89: 0x824B2D68
        virtual void PreUpdateAllStates(float); // 96: 0x824B2DB0
        virtual void ChangeState(unsigned char); // 99: 0x824B5518
        virtual IBehaviourState *GetState(unsigned char); // 100: 0x824B4D38
        virtual void InitBehaviour(); // 101: 0x824B2B08
        virtual void STATE_Enter_Alerted(); // 104: 0x824B3150
        virtual void STATE_Enter_Chasing(); // 108: 0x824B31F0
        virtual void STATE_Enter_Attacking(); // 109: 0x824B3760
        virtual void STATE_Enter_RushAttack(); // 110: 0x824B3ED0
        virtual void STATE_Update_PostSpawn(float); // 115: 0x824B2E18
        virtual void STATE_Update_FacingUp(float); // 117: 0x824B4CC0

    public:
        // CD2 table 0x82109970 differs from FreakBase at these inherited slots.
        virtual void SetReactResupplyPoint(const Fun_Runtime::Vec3 &, const Fun_Runtime::Vec3 &); // slot 85: 0x824A8A90
        virtual void STATE_Update_Chasing(float); // 120: 0x824B3278
        virtual void STATE_Update_RushAttack(float); // 121: 0x824ADFA0
        virtual void STATE_Update_Circling(float); // 125: 0x824B3058
        virtual void STATE_AnimEvent_Attacking(unsigned char, int, short); // 141: 0x824B3940
        virtual void STATE_AnimEvent_RushAttack(unsigned char, int, short); // 142: 0x824B3D28
        virtual void STATE_Attacked_Idle(CHARACTER::cCharacter *, const Fun_Runtime::Vec3 &, cAIEvent *); // 147: 0x824B30A8
        virtual void STATE_Attacked_Ambient(CHARACTER::cCharacter *, const Fun_Runtime::Vec3 &, cAIEvent *); // 148: 0x824B4C78
        virtual void STATE_ReachedDestination_Chasing(bool); // 152: 0x824B35C0
        virtual const char *RetStringForState(unsigned char); // 157: 0x824B8050
        virtual bool OnStuck(); // 161: 0x824B6D80
        virtual void OnRouteEvent(const cBasePatrolRouteEvent &); // 162: 0x824B7020
        virtual void OnFullBodyAnimFinished(); // 165: 0x824B7290
        virtual void OnTargetLost(); // 166: 0x824B6548
        virtual void SetHostileTarget(CHARACTER::cCharacter *); // 171: 0x824B65E8
        virtual float RetMaxTargetHeightDelta() const; // 173: 0x824B7F50

    public:
        // CD2 table 0x82109970 differs from FreakBase at these inherited slots.
        virtual void EnterStateCold(unsigned char); // 102: 0x824BACF0
        virtual void STATE_Enter_Idle(); // 106: 0x824BB7B8
        // CD2's cSafeDeletable table 0x82001740 differs from FreakBase's (0x82109FBC) at this slot.
        virtual void Slot2(); // cSafeDeletable 2: 0x824B73C8
    };
}

#endif

