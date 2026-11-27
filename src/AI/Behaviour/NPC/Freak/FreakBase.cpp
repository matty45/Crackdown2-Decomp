// src/AI/Behaviour/NPC/Freak/FreakBase.cpp
//
// Class: FreakBase (namespace: AI). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is FreakBase.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/AI/Behaviour/NPC/Freak/FreakBase.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/AI/Behaviour/NPC/Freak/FreakBase.cpp

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
#include "AI/cChaseBehaviour.h"
#include "rws/classfactory.h"
#include "AI/FreakBase.h"
#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"
#include "AI/cAiTargetInfo.h"
#include "AI/cAIEventManager.h"
#include "AI/cBasePatrolRouteEvent.h"
#include "CHARACTER/controllerevents.h"
#include <new>

namespace AI
{
    // RuffKing's: the facing (dot product) from which a freak turning to its target starts chasing.
    static const float fSTART_CHASING_DP = 0.866f;

    RWS::CAttributeHandler *FreakBase::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new FreakPrototype(packet);
    }

    const char *FreakBase::RetClassName() const
    {
        return "FreakBase";
    }

    Fun_Runtime::cClass &FreakBase::StaticCreateClass()
    {
        static Fun_Runtime::cClass *FreakBaseClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "FreakBase", 0x120);
        return *FreakBaseClass;
    }

    const Fun_Runtime::cClass *FreakBase::ms_pFreakBaseClass = &FreakBase::StaticCreateClass();

    const Fun_Runtime::cClass &FreakBase::RetClass() const
    {
        return *ms_pFreakBaseClass;
    }

    bool FreakBase::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pFreakBaseClass->IsA(c);
    }

    RWS::CAttributeHandler *FreakBase::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) FreakBase;
        return 0;
    }

    void FreakBase::OnExit()
    {
        if (m_pOnTookDamageSub)
        {
            cAIEventManager::ms_pEventManager->Unsubscribe(m_pOnTookDamageSub);
            m_pOnTookDamageSub = 0;
        }
        if (m_pDestinationReachedSub)
        {
            cAIEventManager::ms_pEventManager->Unsubscribe(m_pDestinationReachedSub);
            m_pDestinationReachedSub = 0;
        }
        if (m_pReactionFinishedSub)
        {
            cAIEventManager::ms_pEventManager->Unsubscribe(m_pReactionFinishedSub);
            m_pReactionFinishedSub = 0;
        }
        if (m_pAcidSackHandle)
        {
            CHARACTER::cCharacter *pCharacter = m_pHost->RetCharacter();
            if (pCharacter)
                pCharacter->TerminateEffect(&m_pAcidSackHandle);
        }
    }

    IBehaviourState *FreakBase::GetState(unsigned char stateIdx)
    {
        // CD2 0x824AC4B0: one state per eFreakBaseState; the Reaction state (14) has no callbacks, and the RushAttack
        // state takes the Attacking state's animation callback.
        static FreakState s_States[eState_FreakStateTotal] =
        {
            FreakState(0, 0, 0, 0, 0, 0, 0),
            FreakState(0, &FreakBase::STATE_Update_PostSpawn, &FreakBase::STATE_Exit_PostSpawn, 0, 0, 0, 0),
            FreakState(&FreakBase::STATE_Enter_Emerging, 0, 0, 0, 0, 0, 0),
            FreakState(0, 0, 0, 0, 0, 0, 0),
            FreakState(&FreakBase::STATE_Enter_Alerted, &FreakBase::STATE_Update_Alerted, &FreakBase::STATE_Exit_Alerted, &FreakBase::STATE_AnimEvent_Alerted, &FreakBase::STATE_Attacked_Alerted, 0, 0),
            FreakState(&FreakBase::STATE_Enter_Idle, &FreakBase::STATE_Update_Idle, &FreakBase::STATE_Exit_Idle, &FreakBase::STATE_AnimEvent_Idle, &FreakBase::STATE_Attacked_Idle, 0, eFlags_CanChangeTarget | eFlags_CanReact),
            FreakState(&FreakBase::STATE_Enter_Ambient, &FreakBase::STATE_Update_Ambient, &FreakBase::STATE_Exit_Ambient, &FreakBase::STATE_AnimEvent_Ambient, &FreakBase::STATE_Attacked_Ambient, 0, eFlags_CanChangeTarget),
            FreakState(&FreakBase::STATE_Enter_Chasing, &FreakBase::STATE_Update_Chasing, &FreakBase::STATE_Exit_Chasing, &FreakBase::STATE_AnimEvent_Chasing, &FreakBase::STATE_Attacked_Chasing, &FreakBase::STATE_ReachedDestination_Chasing, eFlags_CanChangeTarget | eFlags_CanReact),
            FreakState(&FreakBase::STATE_Enter_Circling, &FreakBase::STATE_Update_Circling, 0, 0, 0, 0, eFlags_CanChangeTarget | eFlags_CanReact),
            FreakState(&FreakBase::STATE_Enter_Attacking, &FreakBase::STATE_Update_Attacking, &FreakBase::STATE_Exit_Attacking, &FreakBase::STATE_AnimEvent_Attacking, &FreakBase::STATE_Attacked_Attacking, 0, 0),
            FreakState(&FreakBase::STATE_Enter_RushAttack, &FreakBase::STATE_Update_RushAttack, 0, &FreakBase::STATE_AnimEvent_Attacking, 0, 0, 0),
            FreakState(&FreakBase::STATE_Enter_MoveTo, &FreakBase::STATE_Update_MoveTo, &FreakBase::STATE_Exit_MoveTo, &FreakBase::STATE_AnimEvent_MoveTo, &FreakBase::STATE_Attacked_MoveTo, &FreakBase::STATE_ReachedDestination_MoveTo, eFlags_CanChangeTarget),
            FreakState(&FreakBase::STATE_Enter_FacingUp, &FreakBase::STATE_Update_FacingUp, &FreakBase::STATE_Exit_FacingUp, &FreakBase::STATE_AnimEvent_FacingUp, &FreakBase::STATE_Attacked_FacingUp, 0, eFlags_CanChangeTarget | eFlags_CanReact),
            FreakState(&FreakBase::STATE_Enter_Detonate, 0, &FreakBase::STATE_Exit_Detonate, &FreakBase::STATE_AnimEvent_Detonate, 0, 0, 0),
            FreakState(0, 0, 0, 0, 0, 0, 0),
            FreakState(&FreakBase::STATE_Enter_FollowRoute, &FreakBase::STATE_Update_FollowRoute, &FreakBase::STATE_Exit_FollowRoute, 0, 0, &FreakBase::STATE_ReachedDestination_FollowRoute, 0)
        };
        if (stateIdx >= eState_FreakStateTotal)
            return 0;
        return &s_States[stateIdx];
    }

    bool FreakBase::CanBeAttackedByNPC() const
    {
        return !m_bIsCaged;
    }

    void FreakBase::SetSpawnAction(unsigned char nAction)
    {
        m_nSpawnAction = nAction;
    }

    void FreakBase::OnEnter()
    {
        PlayFreakVOA();
        InitBehaviour();
    }

    void FreakBase::STATE_AnimEvent_RushAttack(unsigned char nType, int nBaseState, short nEventID)
    {
        STATE_AnimEvent_Attacking(nType, nBaseState, nEventID);
    }

    void FreakBase::SetReactResupplyPoint(const Fun_Runtime::Vec3 &vMoveTo, const Fun_Runtime::Vec3 &vHeading)
    {
        m_vReactResupply = vMoveTo;
        m_vRespawnHeading = vHeading;
        m_bReactResupplyPointSet = true;
        ChangeState(eState_MoveTo);
    }

    void FreakBase::OnCharacterEvent(unsigned char eEventType, unsigned char eEventSubType, unsigned char eEvent)
    {
        if (eEventSubType == CHARACTER::eCEST_FullBodyPlayback)
        {
            if (eEvent >= CHARACTER::eCE_Failed && eEvent <= CHARACTER::eCE_Interupted)
                OnFullBodyAnimFinished();
        }
        else if (eEventType == CHARACTER::eCET_Stand && eEventSubType == CHARACTER::eCEST_180
                 && eEvent == CHARACTER::eCE_Finished)
            On180TurnFinished();
    }

    void FreakBase::OnFullBodyAnimFinished()
    {
        if (m_nState == eState_Detonate)
            ChangeState(eState_Null);
    }

    void FreakBase::On180TurnFinished()
    {
        if (m_nState == eState_FacingUp && m_nStateToEnterOnceFacing == eState_Chasing)
        {
            const cAiTargetCache &targetCache = m_pHost->m_TargetCache;
            if (targetCache.RetTargetInfo() && targetCache.RetTargetInfo()->m_fLastFacingTargetDP > fSTART_CHASING_DP)
                RecoverFromInterruption();
        }
    }

    void FreakBase::OnAmbient(const Fun_Runtime::cVectorip<cAnimParams *, 10> &aParams, float fAmbientTimer)
    {
        if (aParams.size())
        {
            ChangeState(eState_Ambient);
            m_fInActivityTimer = fAmbientTimer;
            m_pHost->ActivateAmbientAnimAgent(aParams);
        }
    }

    void FreakBase::OnDied(CHARACTER::cCharacter *, cAIEvent *)
    {
        m_pHost->SetTriggerEventFlags(0);
        m_pHost->m_nPerceptionOptions = 0;
        ChangeState(eState_Null);
    }

    void FreakBase::STATE_Update_FollowRoute(float)
    {
        UpdateStuck();
    }

    void FreakBase::STATE_ReachedDestination_MoveTo(bool bSuccess)
    {
        if (bSuccess)
        {
            m_bReactResupplyPointSet = false;
            if (AcquireNewTarget())
                ChangeState(eState_Chasing);
            else
                ChangeState(eState_Idle);
        }
        else
            ChangeState(eState_MoveTo);
    }

    void FreakBase::STATE_Enter_FacingUp()
    {
        if (m_nStateToEnterOnceFacing && FaceTarget())
        {
            ChangeState(m_nStateToEnterOnceFacing);
            m_nStateToEnterOnceFacing = 0;
        }
    }

    void FreakBase::STATE_Enter_Detonate()
    {
        m_pHost->ActivateFullBodyAnimateAgent(0x1B59F, 0x14);
    }

    void FreakBase::OnFinishedReaction(bool)
    {
        RecoverFromInterruption();
    }

    void FreakBase::STATE_Enter_FollowRoute()
    {
        m_pHost->SetMovementType(2);
    }

    void FreakBase::STATE_ReachedDestination_FollowRoute(bool bSuccess)
    {
        if (!bSuccess)
            MoveToNextRouteNode();
        else
            OnReachedRouteWaypoint();
    }

    void FreakBase::OnReachedRouteEnd()
    {
        if (AcquireNewTarget())
            ChangeState(eState_Chasing);
        else
            ChangeState(eState_Idle);
    }

    bool FreakBase::OnStuck()
    {
        switch (m_nState)
        {
        case eState_FollowRoute:
            MoveToNextRouteNode();
            return true;
        case eState_MoveTo:
            ChangeState(eState_MoveTo);
            return true;
        }
        return false;
    }

    void FreakBase::OnRouteEvent(const cBasePatrolRouteEvent &routeEvent)
    {
        if (routeEvent.RetEventType() == 0)
            ChangeState(eState_Detonate);
    }

    static RWS::CClassFactory::CRegistrar FreakBaseRegistrar(
        "FreakBase", FreakBase::MakeNew, 0x120, false);

    // CD2 0x82F93668: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar FreakBaseNPCBehaviourSMInheritRegistrar(
        AI::FreakBase::StaticCreateClass(), AI::NPCBehaviourSM::StaticCreateClass());

    // CD2 0x82F93720: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar FreakBaseSpawningRegistrar(
        FreakBase::StaticCreateClass(), FreakBase::SpawnFromPrototype);
}
