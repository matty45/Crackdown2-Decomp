#include "rws/attributes.h"
// AI::FreakBase (Crackdown 2): STAND-IN for the class name only. Base AI::NPCBehaviourSM, as in RuffKing's header;
// RetClassName (0x824ABC68) is slot 11 of the vtable at 0x82109378, as cNonGameBase's RetClassName.
#ifndef AI_FREAKBASE_H
#define AI_FREAKBASE_H

#include "AI/NPCBehaviourSM.h"
#include "AI/tBehaviourState.h"
#include "AI/NPCBehaviourPrototype.h"
#include "gom/object_prototype.h"
#include "cd2/layout.h"
#include "fun_runtime/safedeletablepointer.h"
#include "fun_runtime/vec3.h"

namespace CHARACTER { class cCharacterInterface; }
namespace PLAYER { class cPlayer; }
class cGameBase;
namespace VFX { class cParticleEffectInstance; }

namespace AI
{
    class cAIEventSubscription;
    class cBasePatrolRouteEvent;
    // RuffKing: AI::FreakPrototype : NPCBehaviourPrototype, 176 bytes. CD2's FreakBase::MakeNew (0x824ABC10) allocates
    // 0xB0 and calls this constructor (0x824B0B78), which calls NPCBehaviourPrototype's (0x824A8608).
    class FreakPrototype : public NPCBehaviourPrototype
    {
    public:
        FreakPrototype(const RWS::CAttributePacket &);

    private:
        unsigned char m_unmodelled90[0xB0 - 0x90];

        CD2_LAYOUT_CHECKS(FreakPrototype,
            CD2_SIZE(FreakPrototype, 0xB0))
    };

    // RuffKing's; CD2's freak behaviours change to these states (OnFullBodyAnimFinished 0x824AD9B0 leaves Detonate, 13;
    // SetReactResupplyPoint 0x824AD910 enters MoveTo, 11), and RetStringForState's table (0x832B6A98) names them in
    // this order.
    enum eFreakBaseState
    {
        eState_Null = 0,
        eState_PostSpawn,
        eState_Emerging,
        eState_Unconscious,
        eState_Alerted,
        eState_Idle,
        eState_Ambient,
        eState_Chasing,
        eState_Circling,
        eState_H2HAttack,
        eState_RushAttack,
        eState_MoveTo,
        eState_FacingUp,
        eState_Detonate,
        eState_Reaction,
        eState_FollowRoute,
        eState_FreakStateTotal
    };

    // RuffKing's state flags (tBehaviourState's m_nFlags); FreakBase::GetState gives 3 or 1 to the states that allow them.
    enum eFreakStateFlags
    {
        eFlags_CanChangeTarget = 1,
        eFlags_CanReact = 2
    };

    class FreakBase : public AI::NPCBehaviourSM
    {
    public:
        // RuffKing's non-virtual helpers: CD2 0x824AE628 (UpdateStuck), 0x824AF298 (MoveToNextRouteNode), 0x824AF3F8
        // (RecoverFromInterruption).
        void UpdateStuck();
        bool MoveToNextRouteNode();
        void RecoverFromInterruption();
        // RuffKing's; CD2 0x824AF750 (STATE_Enter_FacingUp tests it first, as RuffKing's does).
        bool FaceTarget();
        // Burn's.
        enum eTargetAvailability
        {
            eTarget_NearSideAvailable = 0,
            eTarget_FarSideAvailable,
            eTarget_Surrounded
        };

        // CD2 constructor 0x824ABD60 installs table 0x82109378, 179 primary slots. 101..178: RuffKing's FreakBase virtuals
        // in Burn's order (RuffKing's slot + 7), with CD2's differences in 155..162: two handlers more (155, 159; Notify
        // 0x824AD480 calls them for the events InitBehaviour 0x824ABFC0 subscribes in m_pReactionFinishedSub and
        // m_pDestinationReachedSub; their names are ours), RetStringForState (157) after OnFinishedReaction, and from
        // OnReachedRouteWaypoint (163) on RuffKing's slot + 9. CD2's code lies in RuffKing's source order with these two
        // handlers after OnTookDamage, and every body does what RuffKing's does: OnTookDamage (158) calls OnAcidSackHit
        // (160), RetStringForState (0x824B0B48) returns a state name or "INVALID STATE", OnReachedRouteEnd (164) changes
        // state by AcquireNewTarget (174). The slots holding the empty 0x82580578 are RuffKing's inline empty state
        // callbacks. Signatures are Burn's (RuffKing's for OnTookDamage and OnAcidSackHit).
        virtual void InitBehaviour();
        virtual void EnterStateCold(unsigned char state);
        virtual void STATE_Enter_Emerging();
        virtual void STATE_Enter_Alerted();
        virtual void STATE_Enter_FacingUp();
        virtual void STATE_Enter_Idle();
        virtual void STATE_Enter_Ambient();
        virtual void STATE_Enter_Chasing();
        virtual void STATE_Enter_Attacking();
        virtual void STATE_Enter_RushAttack();
        virtual void STATE_Enter_MoveTo();
        virtual void STATE_Enter_Detonate();
        virtual void STATE_Enter_FollowRoute();
        virtual void STATE_Enter_Circling();
        virtual void STATE_Update_PostSpawn(float dt);
        virtual void STATE_Update_Alerted(float dt);
        virtual void STATE_Update_FacingUp(float dt);
        virtual void STATE_Update_Idle(float dt);
        virtual void STATE_Update_Ambient(float dt);
        virtual void STATE_Update_Chasing(float dt);
        virtual void STATE_Update_RushAttack(float dt);
        virtual void STATE_Update_Attacking(float dt);
        virtual void STATE_Update_MoveTo(float dt);
        virtual void STATE_Update_FollowRoute(float dt);
        virtual void STATE_Update_Circling(float dt);
        virtual void STATE_Exit_PostSpawn();
        virtual void STATE_Exit_Alerted();
        virtual void STATE_Exit_FacingUp();
        virtual void STATE_Exit_Idle();
        virtual void STATE_Exit_Ambient();
        virtual void STATE_Exit_Chasing();
        virtual void STATE_Exit_Attacking();
        virtual void STATE_Exit_MoveTo();
        virtual void STATE_Exit_Detonate();
        virtual void STATE_Exit_FollowRoute();
        virtual void STATE_AnimEvent_Alerted(unsigned char nType, int nBaseState, short nEventID);
        virtual void STATE_AnimEvent_FacingUp(unsigned char nType, int nBaseState, short nEventID);
        virtual void STATE_AnimEvent_Idle(unsigned char nType, int nBaseState, short nEventID);
        virtual void STATE_AnimEvent_Ambient(unsigned char nType, int nBaseState, short nEventID);
        virtual void STATE_AnimEvent_Chasing(unsigned char nType, int nBaseState, short nEventID);
        virtual void STATE_AnimEvent_Attacking(unsigned char nType, int nBaseState, short nEventID);
        virtual void STATE_AnimEvent_RushAttack(unsigned char nType, int nBaseState, short nEventID);
        virtual void STATE_AnimEvent_MoveTo(unsigned char nType, int nBaseState, short nEventID);
        virtual void STATE_AnimEvent_Detonate(unsigned char nType, int nBaseState, short nEventID);
        virtual void STATE_Attacked_Alerted(CHARACTER::cCharacter *pAttacker, const Fun_Runtime::Vec3 &vPosition, cAIEvent *pEvent);
        virtual void STATE_Attacked_FacingUp(CHARACTER::cCharacter *pAttacker, const Fun_Runtime::Vec3 &vPosition, cAIEvent *pEvent);
        virtual void STATE_Attacked_Idle(CHARACTER::cCharacter *pAttacker, const Fun_Runtime::Vec3 &vPosition, cAIEvent *pEvent);
        virtual void STATE_Attacked_Ambient(CHARACTER::cCharacter *pAttacker, const Fun_Runtime::Vec3 &vPosition, cAIEvent *pEvent);
        virtual void STATE_Attacked_Chasing(CHARACTER::cCharacter *pAttacker, const Fun_Runtime::Vec3 &vPosition, cAIEvent *pEvent);
        virtual void STATE_Attacked_Attacking(CHARACTER::cCharacter *pAttacker, const Fun_Runtime::Vec3 &vPosition, cAIEvent *pEvent);
        virtual void STATE_Attacked_MoveTo(CHARACTER::cCharacter *pAttacker, const Fun_Runtime::Vec3 &vPosition, cAIEvent *pEvent);
        virtual void STATE_ReachedDestination_Chasing(bool bSuccess);
        virtual void STATE_ReachedDestination_MoveTo(bool bSuccess);
        virtual void STATE_ReachedDestination_FollowRoute(bool bSuccess);
        virtual void OnReactionFinishedEvent(cAIEvent *pEvent); // CD2 only
        virtual void OnFinishedReaction(bool bSuccess);
        virtual const char *RetStringForState(unsigned char nState);
        virtual void OnTookDamage(cAIEvent *pEvent);
        virtual void OnDestinationReachedEvent(cAIEvent *pEvent); // CD2 only
        virtual void OnAcidSackHit(CHARACTER::cCharacterInterface *pAttacker);
        virtual bool OnStuck();
        virtual void OnRouteEvent(const cBasePatrolRouteEvent &routeEvent);
        virtual void OnReachedRouteWaypoint();
        virtual void OnReachedRouteEnd();
        virtual void OnFullBodyAnimFinished();
        virtual void OnTargetLost();
        virtual void On180TurnFinished();
        virtual bool CheckAndKillOnTODDeath();
        virtual void PlayFreakVOA() const;
        virtual void SpawnAcidSackVFX();
        virtual void SetHostileTarget(CHARACTER::cCharacter *pTarget);
        virtual bool IsAcceptableTarget(CHARACTER::cCharacter &pTarget);
        virtual float RetMaxTargetHeightDelta() const;
        virtual bool AcquireNewTarget();
        virtual void EvaluateTargetAvailability();
        virtual eTargetAvailability CheckTargetAvailability(const cGameBase &target);
        virtual bool TryMoveToFarSideOfTarget(const cGameBase &target);
        virtual const PLAYER::cPlayer *FindAndMoveToNearestAvailablePlayer(float fMaxRange, float fMaxHeightDelta, const PLAYER::cPlayer *pIgnore);

        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        FreakBase();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pFreakBaseClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;

    protected:
        // RuffKing's members in its order, at the offsets CD2's constructor (0x824ABD60) initializes: the safe pointer's
        // table and object at 0xD0/0xDC, four zero words at 0xE0..0xEC, the countdown 0.0 at 0xF0, the route node -1
        // (a halfword) at 0xF4, the last position's three floats at 0x100, the stuck timeout at 0x110 and seven zero
        // bytes from 0x114; the class ends at 0x120 as CD2's registrar gives. CD2 has no cPeriodic members (RuffKing's
        // m_CheckTargetPeriodic and m_CheckAttackPeriodic: no constructor call), and three subscriptions where RuffKing
        // has one: InitBehaviour (0x824ABFC0) subscribes the events 12, 2 and 3 into 0xE0, 0xE4 and 0xE8, OnExit
        // (0x824AC120) unsubscribes the three, and Notify (0x824AD480) hands their events to OnTookDamage (158) and
        // CD2's two handlers 159 and 155 (the names of those two subscriptions are ours). OnExit releases the effect at
        // 0xEC through the character.
        Fun_Runtime::cSafeDeletablePointer<CHARACTER::cCharacterInterface> m_pAcidSackAttacker;    // 0xD0
        cAIEventSubscription *m_pOnTookDamageSub;               // 0xE0
        cAIEventSubscription *m_pDestinationReachedSub;         // 0xE4
        cAIEventSubscription *m_pReactionFinishedSub;           // 0xE8
        VFX::cParticleEffectInstance *m_pAcidSackHandle;        // 0xEC
        float m_fTargetChangeCountDown;                         // 0xF0
        unsigned short m_nNextRouteNode;                        // 0xF4
        Fun_Runtime::Vec3 m_vLastPosition;                      // 0x100
        unsigned int m_nStuckTimeout;                           // 0x110
        unsigned char m_nStateToEnterOnceFacing;                // 0x114
        unsigned char m_nSpawnAction;                           // 0x115
        bool m_bHadTargetLastTick;                              // 0x116
        bool m_bIsTargetFromSquad;                              // 0x117
        bool m_bIsCaged;                                        // 0x118
        bool m_bTriggerAcidSackDetonation;                      // 0x119
        bool m_bMigratedAndEnteredWithoutSpawnPoint;            // 0x11A

        // CD2: FreakBase's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    private:
        CD2_LAYOUT_CHECKS(FreakBase, CD2_SIZE(FreakBase, 0x120)
            CD2_OFFSET(FreakBase, m_pAcidSackAttacker, 0xD0) CD2_OFFSET(FreakBase, m_pOnTookDamageSub, 0xE0)
            CD2_OFFSET(FreakBase, m_pAcidSackHandle, 0xEC) CD2_OFFSET(FreakBase, m_nNextRouteNode, 0xF4)
            CD2_OFFSET(FreakBase, m_vLastPosition, 0x100) CD2_OFFSET(FreakBase, m_nStuckTimeout, 0x110)
            CD2_OFFSET(FreakBase, m_nSpawnAction, 0x115) CD2_OFFSET(FreakBase, m_bIsCaged, 0x118))

    public:
        // CD2 table 0x82109378 differs from NPCBehaviourSM at these inherited slots.
        virtual void OnEnter(); // slot 68: 0x824ABED0
        virtual void OnExit(); // slot 69: 0x824AC120
        virtual void Update(float fDeltaTime); // slot 71: 0x824AD168
        virtual void OnDetectedEnemy(CHARACTER::cCharacter *, const Fun_Runtime::Vec3 &, cAIEvent *); // slot 74: 0x824ADAA0
        virtual void OnHeardSuspiciousSound(CHARACTER::cCharacter *, const Fun_Runtime::Vec3 &, cAIEvent *); // slot 75: 0x824ADBF0
        virtual void OnDied(CHARACTER::cCharacter *, cAIEvent *); // slot 79: 0x824ADC70
        virtual void OnCharacterEvent(unsigned char nEventType, unsigned char nEventSubType, unsigned char nEvent); // slot 80: 0x824AD948
        virtual void OnAmbient(const Fun_Runtime::cVectorip<cAnimParams *, 10> &, float); // slot 83: 0x824ADA20
        virtual void SetReactResupplyPoint(const Fun_Runtime::Vec3 &, const Fun_Runtime::Vec3 &); // slot 85: 0x824AD910
        virtual void SetSpawnAction(unsigned char); // slot 86: 0x824ABCA0
        virtual bool CanBeAttackedByNPC() const; // slot 95: 0x824ABC90
        typedef tBehaviourState<FreakBase> FreakState;
        virtual IBehaviourState *GetState(unsigned char stateIdx); // slot 100: 0x824AC4B0
        // cScriptHost slot 2 (0x824AD480; RuffKing's FreakBase::Notify): the base stand-in declared it before.
        virtual void Slot2();
    };
}

#endif // AI_FREAKBASE_H
