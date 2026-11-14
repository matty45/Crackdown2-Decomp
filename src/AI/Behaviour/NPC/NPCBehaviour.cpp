// Known wrong, left for a structural fix: this file holds two of RuffKing's objects. NPCArmedBehaviour.obj has the initializer run
// from 0x82F913A0 (its header constants, then 0x82F91630 and 0x82F91658) and the code from 0x824A7DD0; NPCBehaviour.obj
// has the run from 0x82F919D0 (to 0x82F91DC0) and the code up to its StaticCreateClass (0x824A87A0). Splitting it
// needs the text boundary between the two objects.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/AIBehaviour.h"
#include "AI/NPCBehaviour.h"
#include "rws/classfactory.h"
#include "AI/NPCArmedBehaviour.h"
#include "AI/BehaviourClassID.h"
#include "gom/proto_registrar.h"
#include "cd2/memory.h"
#include "AI/NPCBehaviourPrototype.h"
#include "editor/guid_event_handler.h"

namespace AI
{
    const char *NPCBehaviour::RetClassName() const
    {
        return "NPCBehaviour";
    }

    // CD2 0x824A7DF0 / 0x824A7E00: slots 0 and 1 of NPCArmedBehaviour's registered-class table (0x82108BD8, which its
    // constructor 0x824A8070 installs); they read the descriptor pointer that 0x82F91630 sets from 0x824A7E80.
    const Fun_Runtime::cClass &NPCArmedBehaviour::RetClass() const
    {
        return *ms_pNPCArmedBehaviourClass;
    }

    bool NPCArmedBehaviour::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pNPCArmedBehaviourClass->IsA(c);
    }

    unsigned char NPCArmedBehaviour::GetStateReplicationInfo() const
    {
        return static_cast<unsigned char>(m_nMainState);
    }

    void NPCArmedBehaviour::OnEnterReplicatedState(unsigned char state)
    {
        OnReplicatedEnter(state);
    }

    Fun_Runtime::cClass &NPCArmedBehaviour::StaticCreateClass()
    {
        static Fun_Runtime::cClass *NPCArmedBehaviourClass =
            new Fun_Runtime::cClass(g_nBehaviourClassID++, "NPCArmedBehaviour", 0xF0);
        return *NPCArmedBehaviourClass;
    }

    const Fun_Runtime::cClass *NPCArmedBehaviour::ms_pNPCArmedBehaviourClass = &NPCArmedBehaviour::StaticCreateClass();

    // CD2 0x82F91658: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar NPCArmedBehaviourNPCBehaviourInheritRegistrar(
        AI::NPCArmedBehaviour::StaticCreateClass(), AI::NPCBehaviour::StaticCreateClass());

    NPCArmedBehaviour::NPCArmedBehaviour()
        : m_nMainState(eMAIN_Null), m_nSubState(0), m_bIsAmbient(false), m_nAmbientAnimID(0)
    {
    }

    void NPCArmedBehaviour::SetReactResupplyPoint(const Fun_Runtime::Vec3 &position, const Fun_Runtime::Vec3 &heading)
    {
        m_vReactResupply = position;
        m_vRespawnHeading = heading;
        m_bReactResupplyPointSet = true;
        ChangeMainState(eMAIN_ReactResupply);
    }

    void NPCArmedBehaviour::OnReplicatedEnter(unsigned char state)
    {
        OnEnter();
        ChangeMainState(static_cast<eState>(state));
    }

    void NPCArmedBehaviour::Slot71()
    {
        switch (m_nMainState)
        {
        case eMAIN_Idle:
            OnIdle();
            break;
        case eMAIN_Investigate:
            OnInvestigating();
            break;
        case eMAIN_Patrol:
            OnPatrolling();
            break;
        case eMAIN_Attack:
            OnAttacking();
            break;
        case eMAIN_Cover:
            OnCover();
            break;
        case eMAIN_Retreat:
            OnRetreating();
            break;
        case eMAIN_ReactResupply:
            OnReactResupply();
            break;
        case eMAIN_Ambient:
            OnAmbient();
            break;
        case eMAIN_Drive:
            OnDrive();
            break;
        }
    }

    void NPCArmedBehaviour::ChangeMainState(eState state)
    {
        m_nMainState = state;
    }

    void NPCArmedBehaviour::ChangeSubState(unsigned int state)
    {
        ExitSubState();
        EnterSubState(state);
    }

    void NPCArmedBehaviour::EnterSubState(unsigned int state)
    {
        m_nSubState = state;
        switch (m_nMainState)
        {
        case eMAIN_Idle:
            EnterSubStateIdle();
            break;
        case eMAIN_Investigate:
            EnterSubStateInvestigating();
            break;
        case eMAIN_Patrol:
            EnterSubStatePatrolling();
            break;
        case eMAIN_Attack:
            EnterSubStateAttacking();
            break;
        case eMAIN_Cover:
            EnterSubStateCover();
            break;
        case eMAIN_Retreat:
            EnterSubStateRetreating();
            break;
        case eMAIN_ReactResupply:
            EnterSubStateReactResupply();
            break;
        case eMAIN_Ambient:
            EnterSubStateAmbient();
            break;
        case eMAIN_Drive:
            EnterSubStateDrive();
            break;
        }
    }

    void NPCArmedBehaviour::ExitSubState()
    {
        switch (m_nMainState)
        {
        case eMAIN_Idle:
            ExitSubStateIdle();
            break;
        case eMAIN_Investigate:
            ExitSubStateInvestigating();
            break;
        case eMAIN_Patrol:
            ExitSubStatePatrolling();
            break;
        case eMAIN_Attack:
            ExitSubStateAttacking();
            break;
        case eMAIN_Cover:
            ExitSubStateCover();
            break;
        case eMAIN_Retreat:
            ExitSubStateRetreating();
            break;
        case eMAIN_ReactResupply:
            ExitSubStateReactResupply();
            break;
        case eMAIN_Ambient:
            ExitSubStateAmbient();
            break;
        case eMAIN_Drive:
            ExitSubStateDrive();
            break;
        }
    }

    NPCBehaviourPrototype::NPCBehaviourPrototype(const RWS::CAttributePacket &packet)
        : AIBehaviour::AIBehaviourPrototype(packet), mPrimary(Editor::g_GUIDNull)
    {
    }

    const RWS::RWSGUID &NPCBehaviourPrototype::RetPrimaryWeapon() const
    {
        return mPrimary;
    }

    // NPCBehaviour's constructor is 0x824A89C8, outside this scaffold's text range.
    RWS::CAttributeHandler *NPCBehaviour::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        return new (memory) NPCBehaviour;
    }

    RWS::CAttributeHandler *NPCBehaviour::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new NPCBehaviour();
    }

    const Fun_Runtime::cClass &NPCBehaviour::RetClass() const
    {
        return *ms_pNPCBehaviourClass;
    }

    void NPCBehaviour::OnEnterReplicatedState(unsigned char)
    {
        OnEnter();
    }

    Fun_Runtime::cClass &NPCBehaviour::StaticCreateClass()
    {
        static Fun_Runtime::cClass *NPCBehaviourClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "NPCBehaviour", 0xC0);
        return *NPCBehaviourClass;
    }

    const Fun_Runtime::cClass *NPCBehaviour::ms_pNPCBehaviourClass = &NPCBehaviour::StaticCreateClass();

    // CD2 0x82F91D08: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar NPCBehaviourAIBehaviourInheritRegistrar(
        AI::NPCBehaviour::StaticCreateClass(), AI::AIBehaviour::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar NPCBehaviourRegistrar(
        "NPCBehaviour", NPCBehaviour::MakeNew, 0xC0, false);

    static GOM::cProtoRegistrar NPCBehaviourSpawningRegistrar(
        NPCBehaviour::StaticCreateClass(), NPCBehaviour::SpawnFromPrototype);
}
