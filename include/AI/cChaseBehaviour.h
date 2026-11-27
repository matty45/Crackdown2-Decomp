// AI::cChaseBehaviour (Crackdown 2): the vehicle chase behaviour, 0x100 bytes. RuffKing's ChaseBehaviour.h: an
// NPCBehaviourSM and a cNPCArmourySetup. CD2's constructor 0x824CE6B0 calls NPCBehaviourSM's (0x824ABA30), installs the
// tables 0x8210BCA8 (primary, 119 slots), 0x8210B4D8, 0x8210B6F0, 0x8210BE84 and 0x8212CED0 and sets the fields below
// (RuffKing's names and order, at CD2's offsets from that constructor).
// Its own virtuals 101..118 are RuffKing's (EnterIdle .. OnTargetAcquired, its offsets 284..348) in RuffKing's order,
// with one CD2 slot more: 114, the exit callback of the Holding state (GetState 0x824CF188 builds that state from 105,
// 112 and 114; the name is ours). Every state's callbacks are the ones GetState stores; the empty ones fold to
// 0x82580578. CD2's table overrides 11, 68, 69, 72, 74, 75 (one body), 96 and 100, and slot 2 of the cScriptHost table.
// m_bClearTargetOnDeath (0xF6) is CD2's alone; PreUpdateAllStates (0x824CEC18) tests it with the target's alive flag.
#ifndef AI_CCHASEBEHAVIOUR_H
#define AI_CCHASEBEHAVIOUR_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"
#include "fun_runtime/vec3.h"
#include "cd2/layout.h"
#include "AI/BehaviourClassID.h"
#include "AI/NPCBehaviourSM.h"
#include "AI/NPCBehaviourPrototype.h"
#include "AI/cNPCArmourySetup.h"
#include "AI/tBehaviourState.h"
#include "AI/cAiPlayer.h"

namespace AI
{
    class cAIEventSubscription;

    class cChaseBehaviour : public NPCBehaviourSM, public cNPCArmourySetup
    {
    public:
        enum eChaseState
        {
            eState_Null = 0,
            eState_Idle,
            eState_Chasing,
            eState_Follow,
            eState_DriveFleeing,
            eState_Holding,
            eState_DrivingTraffic,
            eState_ChaseTotal
        };

        class cChaseBehaviourPrototype : public NPCBehaviourPrototype
        {
        public:
            __forceinline cChaseBehaviourPrototype(const RWS::CAttributePacket &packet) : NPCBehaviourPrototype(packet) {}
            virtual void HandleAttributes(const RWS::CAttributePacket &);

            CD2_LAYOUT_CHECKS(cChaseBehaviourPrototype,
                CD2_SIZE(cChaseBehaviourPrototype, 0x90))
        };

        static Fun_Runtime::cClass *const ms_pcChaseBehaviourClass;
        static const char *const pcChaseBehaviourClassID;

        cChaseBehaviour();
        virtual const char *RetClassName() const;
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;

        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *proto, void *mem);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);

        virtual void OnEnter();
        virtual void OnExit();
        virtual void OnEnterReplicatedState(unsigned char nReplicatedState);
        virtual void OnDetectedEnemy(CHARACTER::cCharacter *pEnemy, const Fun_Runtime::Vec3 &vPosition, cAIEvent *pEvent);
        virtual void OnHeardSuspiciousSound(CHARACTER::cCharacter *pSource, const Fun_Runtime::Vec3 &vPosition,
                                            cAIEvent *pEvent);
        virtual void PreUpdateAllStates(float fDeltaTime);

        // 101..118
        virtual void EnterIdle();
        virtual void EnterChasing();
        virtual void EnterFollow();
        virtual void EnterDriveFleeing();
        virtual void EnterHolding();
        virtual void EnterDrivingTraffic();
        virtual void UpdateVehicleSubs();
        virtual void OnUpdateIdle(float fDeltaTime);
        virtual void OnUpdateChasing(float fDeltaTime);
        virtual void OnUpdateFollow(float fDeltaTime);
        virtual void OnUpdateDriveFleeing(float fDeltaTime);
        virtual void OnUpdateHolding(float fDeltaTime);
        virtual void OnUpdateDrivingTraffic(float fDeltaTime);
        virtual void ExitHolding();
        virtual cNonGameBase *GetSpawnedAmbientTarget();
        virtual unsigned int RetTargetingFlags() const;
        virtual void OnTargetLost();
        virtual void OnTargetAcquired();

        void SetTargetAndEnemy(CHARACTER::cCharacter *pTarget);
        // RuffKing's out-of-line ClearTargetAndEnemy clears the target cache; CD2 expands it in PreUpdateAllStates
        // (0x824CEC18) and cAgressiveResponseChaseBehaviour::EnterIdleGuard (0x824CAE60), with the host's ClearEnemy first.
        void ClearTargetAndEnemy()
        {
            m_pHost->ClearEnemy();
            m_pHost->m_TargetCache.ClearTarget();
        }
        // RuffKing's; CD2 expands it in PreUpdateAllStates.
        void LockTarget(bool bLock) { m_bTargetLocked = bLock; }

        // cScriptHost slot 2: cChaseBehaviour's own (0x824CE808).
        virtual void Slot2();

    protected:
        typedef tBehaviourState<cChaseBehaviour> ChaseState;
        virtual IBehaviourState *GetState(unsigned char stateIdx);
        bool TryBindAmbientTarget();

        cAIEventSubscription *m_pVehicleCollisionSub;   // 0xD0
        float m_fTimeFleeing;                           // 0xD4
        Fun_Runtime::Vec3 m_vFleeDangerPosition;        // 0xE0
        unsigned int m_nInitialEdge;                    // 0xF0
        bool m_bFollowMode;                             // 0xF4
        bool m_bTargetLocked;                           // 0xF5
        bool m_bClearTargetOnDeath;                     // 0xF6: name ours

    public:
        CD2_LAYOUT_CHECKS(cChaseBehaviour,
            CD2_SIZE(cChaseBehaviour, 0x100)
            CD2_OFFSET(cChaseBehaviour, m_pVehicleCollisionSub, 0xD0)
            CD2_OFFSET(cChaseBehaviour, m_vFleeDangerPosition, 0xE0)
            CD2_OFFSET(cChaseBehaviour, m_nInitialEdge, 0xF0)
            CD2_OFFSET(cChaseBehaviour, m_bClearTargetOnDeath, 0xF6))
    };
}

#endif
