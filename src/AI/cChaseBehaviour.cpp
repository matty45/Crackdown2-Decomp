// AI/cChaseBehaviour.cpp: cChaseBehaviour, the vehicle chase behaviour of Crackdown 2 (RuffKing's
// AI/Behaviour/NPC/Vehicle/ChaseBehaviour.cpp).

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/NPCBehaviour.h"
#include "AI/cChaseBehaviour.h"
#include "AI/cAIEventManager.h"
#include "AI/cAiPlayer.h"
#include "AI/cAiTargetInfo.h"
#include "CHARACTER/cCharacter.h"
#include "Vehicle/cVehicle.h"
#include "VEHICLE_CONTROL/cHelicopterController.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include <new>

namespace AI
{
    const char *const cChaseBehaviour::pcChaseBehaviourClassID = "cChaseBehaviour";
    Fun_Runtime::cClass *const cChaseBehaviour::ms_pcChaseBehaviourClass = &cChaseBehaviour::StaticCreateClass();

    const char *cChaseBehaviour::RetClassName() const
    {
        return pcChaseBehaviourClassID;
    }

    cChaseBehaviour::cChaseBehaviour()
        : m_pVehicleCollisionSub(0), m_nInitialEdge(-1), m_bFollowMode(false), m_bTargetLocked(false),
          m_bClearTargetOnDeath(true)
    {
    }

    RWS::CAttributeHandler *cChaseBehaviour::SpawnFromPrototype(GOM::cObjectPrototype *, void *mem)
    {
        if (mem)
            return new (mem) cChaseBehaviour;
        return 0;
    }

    void cChaseBehaviour::OnEnter()
    {
        static_cast<NPCBehaviourPrototype *>(m_pPrototype)->SetupWeapons(m_pHost);
        m_pHost->m_nPerceptionOptions = 0x41;
        m_pHost->SetTriggerEventFlags(0xBF);
        m_pVehicleCollisionSub = 0;
        ChangeState(eState_Idle);
    }

    void cChaseBehaviour::OnExit()
    {
        if (m_pVehicleCollisionSub)
            m_pVehicleCollisionSub = cAIEventManager::ms_pEventManager->Unsubscribe(m_pVehicleCollisionSub);
    }

    void cChaseBehaviour::EnterDrivingTraffic()
    {
        m_pHost->ActivateAmbientTrafficDrivingAgent(m_nInitialEdge, false);
        m_nInitialEdge = -1;
    }

    void cChaseBehaviour::OnUpdateDriveFleeing(float fDeltaTime)
    {
        m_fTimeFleeing += fDeltaTime;
        if (m_fTimeFleeing > 5.0f)
            ChangeState(eState_DrivingTraffic);
    }

    void cChaseBehaviour::OnDetectedEnemy(CHARACTER::cCharacter *pEnemy, const Fun_Runtime::Vec3 &, cAIEvent *)
    {
        if (m_fInActivityTimer <= 0.0001f && !m_bTargetLocked)
        {
            SetTargetAndEnemy(pEnemy);
            OnTargetAcquired();
        }
    }

    void cChaseBehaviour::SetTargetAndEnemy(CHARACTER::cCharacter *pTarget)
    {
        if (pTarget)
        {
            cAiTargetCache &targetCache = m_pHost->m_TargetCache;
            targetCache.SetTarget(pTarget, pTarget->RetScriptPosition(), RetTargetingFlags());
            m_pHost->SetEnemy(pTarget, 4);
        }
    }

    bool cChaseBehaviour::TryBindAmbientTarget()
    {
        cNonGameBase *pTarget = GetSpawnedAmbientTarget();
        if (pTarget && pTarget->IsA(*CHARACTER::cCharacter::ms_pcCharacterClass) && pTarget->IsAlive())
        {
            SetTargetAndEnemy(static_cast<CHARACTER::cCharacter *>(pTarget));
            return true;
        }
        return false;
    }

    void cChaseBehaviour::OnTargetLost()
    {
        ChangeState(eState_DrivingTraffic);
    }

    void cChaseBehaviour::OnTargetAcquired()
    {
        if (m_bFollowMode)
            ChangeState(eState_Follow);
        else
            ChangeState(eState_Chasing);
    }

    Fun_Runtime::cClass &cChaseBehaviour::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cChaseBehaviour_Class =
            new Fun_Runtime::cClass(g_nBehaviourClassID++, "cChaseBehaviour", 0x100);
        return *cChaseBehaviour_Class;
    }

    const Fun_Runtime::cClass &cChaseBehaviour::RetClass() const
    {
        return *ms_pcChaseBehaviourClass;
    }

    bool cChaseBehaviour::IsA(const Fun_Runtime::cClass &test) const
    {
        return ms_pcChaseBehaviourClass->IsA(test);
    }

    void cChaseBehaviour::cChaseBehaviourPrototype::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        HandleAttributesBase(packet);
        HandleAttributesNPC(packet);
        for (RWS::CAttributeCommandIterator it(packet, pcChaseBehaviourClassID); !it.IsFinished(); ++it)
        {
        }
    }

    RWS::CAttributeHandler *cChaseBehaviour::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cChaseBehaviourPrototype(packet);
    }

    static RWS::CClassFactory::CRegistrar cChaseBehaviourRegistrar("cChaseBehaviour", cChaseBehaviour::MakeNew, 0x100, false);

    void cChaseBehaviour::EnterDriveFleeing()
    {
        Vehicle::cVehicle *pVehicle = m_pHost->RetCharacter()->RetVehicle();
        if (pVehicle)
        {
            m_fTimeFleeing = 0.0f;
            m_pHost->ActivateFleeingDangerAgent(m_vFleeDangerPosition);
            VEHICLE_CONTROL::cVehicleController *pController = pVehicle->RetPtrVehicleController();
            if (pController)
                pController->SetSpeedLimit(pController->GetSpeedLimit() < 60.0f ? pController->GetSpeedLimit() : 60.0f);
        }
    }

    void cChaseBehaviour::UpdateVehicleSubs()
    {
        if (m_pHost->RetCharacter()->RetVehicle())
        {
            if (!m_pVehicleCollisionSub)
                m_pVehicleCollisionSub = SubscribeImmediate(106, m_pHost->RetCharacter()->RetVehicle(),
                                                            Fun_Runtime::g_GlobalConstants.CONST_INT_0);
        }
        else if (m_pVehicleCollisionSub)
            m_pVehicleCollisionSub = cAIEventManager::ms_pEventManager->Unsubscribe(m_pVehicleCollisionSub);
    }

    void cChaseBehaviour::PreUpdateAllStates(float fDeltaTime)
    {
        UpdateVehicleSubs();
        if (m_nState && !m_pHost->IsAlive())
            ChangeState(eState_Null);
        if (m_fInActivityTimer > 0.0001f)
        {
            float fTimer = m_fInActivityTimer - fDeltaTime;
            if (fTimer < 0.0001f)
                fTimer = 0.0f;
            m_fInActivityTimer = fTimer;
        }
        if (!m_pHost->RetCharacter()->RetTargetScriptHost())
        {
            if (TryBindAmbientTarget())
            {
                LockTarget(true);
                OnTargetAcquired();
            }
            else
                LockTarget(false);
        }
        const cAiTargetCache &targetCache = m_pHost->m_TargetCache;
        if (targetCache.RetTargetInfo()
            && ((!targetCache.RetTargetInfo()->IsTargetAlive() && m_bClearTargetOnDeath)
                || targetCache.RetTargetInfo()->IsTargetDeleted()))
        {
            ClearTargetAndEnemy();
            LockTarget(false);
            OnTargetLost();
        }
    }

    void cChaseBehaviour::OnUpdateIdle(float)
    {
        if (m_pHost->RetCharacter()->RetTarget())
        {
            OnTargetAcquired();
            return;
        }
        if (m_pHost->RetCharacter()->RetVehicle() && m_pHost->RetCharacter()->RetVehicle()->RetPtrVehicleController())
            ChangeState(eState_DrivingTraffic);
    }

    IBehaviourState *cChaseBehaviour::GetState(unsigned char stateIdx)
    {
        static ChaseState s_States[eState_ChaseTotal] =
        {
            ChaseState(0, 0, 0, 0, 0, 0, 0),
            ChaseState(&cChaseBehaviour::EnterIdle, &cChaseBehaviour::OnUpdateIdle, 0, 0, 0, 0, 0),
            ChaseState(&cChaseBehaviour::EnterChasing, &cChaseBehaviour::OnUpdateChasing, 0, 0, 0, 0, 0),
            ChaseState(&cChaseBehaviour::EnterFollow, &cChaseBehaviour::OnUpdateFollow, 0, 0, 0, 0, 0),
            ChaseState(&cChaseBehaviour::EnterDriveFleeing, &cChaseBehaviour::OnUpdateDriveFleeing, 0, 0, 0, 0, 0),
            ChaseState(&cChaseBehaviour::EnterHolding, &cChaseBehaviour::OnUpdateHolding, &cChaseBehaviour::ExitHolding,
                       0, 0, 0, 0),
            ChaseState(&cChaseBehaviour::EnterDrivingTraffic, &cChaseBehaviour::OnUpdateDrivingTraffic, 0, 0, 0, 0, 0)
        };
        if (stateIdx >= eState_ChaseTotal)
            return 0;
        return &s_States[stateIdx];
    }

    // CD2 0x82F9A108: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cChaseBehaviourNPCBehaviourInheritRegistrar(
        AI::cChaseBehaviour::StaticCreateClass(), AI::NPCBehaviour::StaticCreateClass());

    // CD2 0x82F9A1C0: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cChaseBehaviourSpawningRegistrar(
        cChaseBehaviour::StaticCreateClass(), cChaseBehaviour::SpawnFromPrototype);
}
