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
#include "AI/cAgressiveResponseBase.h"
#include "AI/cAgressiveResponseChaseBehaviour.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"
#include "Vehicle/cVehicle.h"

namespace AI
{
    const Fun_Runtime::cClass *cAgressiveResponseChaseBehaviour::ms_pcAgressiveResponseChaseBehaviourClass = &cAgressiveResponseChaseBehaviour::StaticCreateClass();

    RWS::CAttributeHandler *cAgressiveResponseChaseBehaviour::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cAgressiveResponseChaseBehaviourPrototype(packet);
    }

    const Fun_Runtime::cClass &cAgressiveResponseChaseBehaviour::RetClass() const
    {
        return *ms_pcAgressiveResponseChaseBehaviourClass;
    }

    const char *cAgressiveResponseChaseBehaviour::RetClassName() const
    {
        return "cAgressiveResponseChaseBehaviour";
    }

    RWS::CAttributeHandler *cAgressiveResponseChaseBehaviour::SpawnFromPrototype(GOM::cObjectPrototype *pPrototype, void *pMem)
    {
        if (pMem)
            return new (pMem) cAgressiveResponseChaseBehaviour(pPrototype);
        return 0;
    }

    bool cAgressiveResponseChaseBehaviour::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcAgressiveResponseChaseBehaviourClass->IsA(c);
    }

    static RWS::CClassFactory::CRegistrar cAgressiveResponseChaseBehaviourRegistrar(
        "cAgressiveResponseChaseBehaviour", cAgressiveResponseChaseBehaviour::MakeNew, 0x140, false);

    Fun_Runtime::cClass &cAgressiveResponseChaseBehaviour::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAgressiveResponseChaseBehaviourClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "cAgressiveResponseChaseBehaviour", 0x140);
        return *cAgressiveResponseChaseBehaviourClass;
    }

    unsigned int cAgressiveResponseChaseBehaviour::RetTargetingFlags() const
    {
        return 0x4006;
    }

    void cAgressiveResponseChaseBehaviour::PostUpdateAllStates(float)
    {
        if (m_nState && LookForCover())
            ChangeState(eState_MoveToCover);
    }

    void cAgressiveResponseChaseBehaviour::ExitGettingOut()
    {
        m_bTargetLocked = false;
    }

    void cAgressiveResponseChaseBehaviour::ExitMoveToCover()
    {
        if (!m_bTransitioningToCover)
            m_pCoverPoint = 0;
    }

    void cAgressiveResponseChaseBehaviour::ExitEngagingFromCover()
    {
        m_pCoverPoint = 0;
    }

    void cAgressiveResponseChaseBehaviour::EnterIdleOccluded()
    {
        m_pHost->PlayGenericFullBodyAnimation(0xC35CB, 0x10);
    }

    void cAgressiveResponseChaseBehaviour::EnterIdleGuard()
    {
        ClearTargetAndEnemy();
        m_pHost->SetTriggerEventFlags(0xFF);
    }

    void cAgressiveResponseChaseBehaviour::OnCharacterEvent(unsigned char nEventType, unsigned char, unsigned char nEvent)
    {
        if (nEventType == 1 && (nEvent == 3 || nEvent == 4 || nEvent == 2))
            OnFullbodyAnimFinishedOrInterrupted();
    }

    void cAgressiveResponseChaseBehaviour::OnTargetLost()
    {
        if (m_nState < eState_ARCBFirstState)
            ChangeState(eState_DrivingTraffic);
        else
            ChangeState(eState_IdleGuard);
    }

    // CD2 0x82F99460: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cAgressiveResponseChaseBehaviourcAgressiveResponseBaseInheritRegistrar(
        AI::cAgressiveResponseChaseBehaviour::StaticCreateClass(), AI::cAgressiveResponseBase::StaticCreateClass());

    // CD2 0x82F99518: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cAgressiveResponseChaseBehaviourSpawningRegistrar(
        cAgressiveResponseChaseBehaviour::StaticCreateClass(), cAgressiveResponseChaseBehaviour::SpawnFromPrototype);
}
