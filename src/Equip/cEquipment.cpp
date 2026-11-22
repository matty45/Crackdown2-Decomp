// src/Equip/cEquipment.cpp
//
// Class: cEquipment (namespace: Equip). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cEquipment.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/cEquipment.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/cEquipment.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "PHYSICS/cNetDynamicBody.h"
#include "rws/classfactory.h"
#include "Equip/cEquipment.h"
#include "cd2/memory.h"
#include "fun_runtime/script_type_registrar.h"
#include "Activity/cActivityManager.h"
#include "rws/time.h"
#include "CHARACTER/cPlayerNetManager.h"
#include "PHYSICS/cPhysicsWorld.h"
#include "Havok/hkRigidBody.h"

namespace Equip
{
    const Fun_Runtime::cClass *cEquipment::ms_pcEquipmentClass = &cEquipment::StaticCreateClass();

    const Fun_Runtime::cClass &cEquipment::RetClass() const
    {
        return *ms_pcEquipmentClass;
    }

    bool cEquipment::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcEquipmentClass->IsA(c);
    }

    int cEquipment::RetUpperAimIndex() const
    {
        return -1;
    }

    bool cEquipment::IsMarkedForDeletion()
    {
        return m_bMarkedForDeletion;
    }

    Fun_Runtime::cClass &cEquipment::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cEquipmentClass = new Fun_Runtime::cClass(0x6, "cEquipment", 0x870);
        return *cEquipmentClass;
    }

    void cEquipment::STATE_Deactivated::BeginState(Fun_Runtime::cStateMachine *)
    {
    }

    void cEquipment::STATE_Deactivated::Process(Fun_Runtime::cStateMachine *)
    {
    }

    void cEquipment::STATE_Deactivated::EndState(Fun_Runtime::cStateMachine *)
    {
    }

    inline Fun_Runtime::State *cEquipment::StaticRetSTATE_Deactivated()
    {
        static STATE_Deactivated s_State;
        return &s_State;
    }

    Fun_Runtime::State *cEquipment::RetSTATE_Deactivated() const
    {
        return StaticRetSTATE_Deactivated();
    }

    Fun_Runtime::State *cEquipment::RetSTATE_Deactivated()
    {
        return StaticRetSTATE_Deactivated();
    }

    void cEquipment::STATE_Idle::BeginState(Fun_Runtime::cStateMachine *)
    {
    }

    void cEquipment::STATE_Idle::Process(Fun_Runtime::cStateMachine *)
    {
    }

    void cEquipment::STATE_Idle::EndState(Fun_Runtime::cStateMachine *)
    {
    }

    inline Fun_Runtime::State *cEquipment::StaticRetSTATE_Idle()
    {
        static STATE_Idle s_State;
        return &s_State;
    }

    Fun_Runtime::State *cEquipment::RetSTATE_Idle() const
    {
        return StaticRetSTATE_Idle();
    }

    Fun_Runtime::State *cEquipment::RetSTATE_Idle()
    {
        return StaticRetSTATE_Idle();
    }

    void cEquipment::STATE_Active::BeginState(Fun_Runtime::cStateMachine *)
    {
    }

    void cEquipment::STATE_Active::Process(Fun_Runtime::cStateMachine *pSM)
    {
        cEquipment *pEquipment = static_cast<cEquipment *>(pSM);
        pEquipment->m_fTimer -= RWS::Time::RetDeltaTimeSecs();
        if (pEquipment->m_fTimer < 0.0001f)
            pEquipment->GoTo_State(pEquipment->RetSTATE_Idle());
    }

    void cEquipment::STATE_Active::EndState(Fun_Runtime::cStateMachine *)
    {
    }

    inline Fun_Runtime::State *cEquipment::StaticRetSTATE_Active()
    {
        static STATE_Active s_State;
        return &s_State;
    }

    Fun_Runtime::State *cEquipment::RetSTATE_Active() const
    {
        return StaticRetSTATE_Active();
    }

    Fun_Runtime::State *cEquipment::RetSTATE_Active()
    {
        return StaticRetSTATE_Active();
    }

    void cEquipment::STATE_Paused::BeginState(Fun_Runtime::cStateMachine *)
    {
    }

    void cEquipment::STATE_Paused::Process(Fun_Runtime::cStateMachine *pSM)
    {
        cEquipment *pEquipment = static_cast<cEquipment *>(pSM);
        pEquipment->m_fTimer -= RWS::Time::RetDeltaTimeSecs();
        if (pEquipment->m_fTimer < 0.0001f)
            pEquipment->GoTo_State(pEquipment->RetSTATE_Idle());
    }

    void cEquipment::STATE_Paused::EndState(Fun_Runtime::cStateMachine *)
    {
    }

    inline Fun_Runtime::State *cEquipment::StaticRetSTATE_Paused()
    {
        static STATE_Paused s_State;
        return &s_State;
    }

    Fun_Runtime::State *cEquipment::RetSTATE_Paused() const
    {
        return StaticRetSTATE_Paused();
    }

    Fun_Runtime::State *cEquipment::RetSTATE_Paused()
    {
        return StaticRetSTATE_Paused();
    }

    static RWS::CClassFactory::CRegistrar cEquipmentRegistrar(
        "cEquipment", cEquipment::MakeNew, 0x870, false);

    // CD2 0x82FCB1E8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cEquipmentcNetDynamicBodyInheritRegistrar(
        Equip::cEquipment::StaticCreateClass(), PHYSICS::cNetDynamicBody::StaticCreateClass());

    // CD2 0x82FCB2A0: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cEquipmentSpawningRegistrar(
        cEquipment::StaticCreateClass(), cEquipment::SpawnFromPrototype);

    RWS::CAttributeHandler *cEquipment::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cEquipmentPrototype(packet);
    }

    const char *cEquipment::RetClassName() const
    {
        return "cEquipment";
    }

    RWS::CAttributeHandler *cEquipment::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cEquipment;
        return 0;
    }

    // CD2 script-type registration; constructor/table evidence identifies the child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cEquipment> cEquipmentScriptRegistrar(
        "cEquipment", "cDynamicBody");

    const Fun_Runtime::cScriptTypeRegistration *cEquipment::RetScriptTypeRegistration() const
    {
        return &cEquipmentScriptRegistrar;
    }

    cEquipment::~cEquipment()
    {
        SetOwner(0);
    }

    float cEquipment::cEquipmentPrototype::RetDroppedDeletionTime() const
    {
        return m_fDroppedDeletionTime;
    }

    bool cEquipment::cEquipmentPrototype::CanZoom() const
    {
        return m_bCanZoom && m_fMaxZoomFactor > 0.0f;
    }

    float cEquipment::cEquipmentPrototype::RetMaxZoomFactor() const
    {
        return m_fMaxZoomFactor;
    }

    float cEquipment::cEquipmentPrototype::RetZoomSpeed() const
    {
        return m_fZoomSpeed;
    }

    int cEquipment::cEquipmentPrototype::RetInInvPickupVFXID() const
    {
        return m_nInInvPickupId;
    }

    int cEquipment::cEquipmentPrototype::RetNotInInvPickupVFXID() const
    {
        return m_nNotInInvPickupId;
    }

    bool cEquipment::cEquipmentPrototype::RetLoadedCmdSpawn() const
    {
        return m_bLoadedCmdSpawn;
    }

}

// CD2 folds the shared event-handler getter into this translation unit. cEquipment's script registrar (0x82604A94)
// registers this address as "RetOwner", so the surviving copy is probably the inline cNonGameBase::RetOwner (the same
// +0x4C load); it can take that name once the registrar is written.
int cNonGameBase::RetUniqueID()
{
    return m_nUniqueID;
}

namespace Equip
{
    void cEquipment::CreateHavokPhysics()
    {
        CreateBodyPhysics();
    }

    void cEquipment::DeleteHavokPhysics()
    {
        if (m_pRigidBody)
            DeleteBodyPhysics();
    }

    void cEquipment::ResetHavokPhysics()
    {
        DeleteHavokPhysics();
        CreateHavokPhysics();
    }

    GOM::cPointOfInterest *cEquipment::RetPointOfInterest(int)
    {
        return &m_POI;
    }

    unsigned int cEquipment::GetID() const
    {
        return static_cast<const cEquipmentPrototype *>(m_pPrototype)->GetID();
    }

    eEquipmentType cEquipment::RetEquipmentType() const
    {
        return static_cast<const cEquipmentPrototype *>(m_pPrototype)->RetEquipmentType();
    }

    Fun_Runtime::Mtx *cEquipment::GetMatrix(Fun_Runtime::Mtx &Mat)
    {
        cGameBase *pOwner = RetOwnerGameObject();
        if (pOwner)
            pOwner->GetAimMatrix(Mat);
        return &Mat;
    }

    void cEquipment::LeaveRenderableState()
    {
        if (!m_bMultiplayerPickup)
            PHYSICS::cDynamicBody::LeaveRenderableState();
    }

    void cEquipment::EnterGhostState()
    {
        if (!m_bGhostState)
        {
            PHYSICS::cDynamicBody::EnterGhostState();
            if (m_pRigidBody)
            {
                m_pRigidBody->addReference();
                if (m_pRigidBody->m_world)
                    m_pMyWorld->removeEntity(m_pRigidBody);
            }
        }
    }

    bool cEquipment::PickUpRequested(cGameBase *pOwnerTest)
    {
        return !IsMarkedForDeletion() && (GetStatus() == STATUS_FREE || GetStatus() == STATUS_MOUNTED) && !IsLive()
            && (RetOwner() == pOwnerTest || !RetOwner());
    }

    bool cEquipment::CanBeEquipped()
    {
        return !IsMarkedForDeletion();
    }

    bool cEquipment::IsManagedByActivityManager()
    {
        return !m_bMultiplayerPickup;
    }

    void cEquipment::CalculateLOD(int nNodeID)
    {
        m_LOD[nNodeID] = RetNetworkLOD(CHARACTER::cPlayerNetManager::RetNetCharacter(nNodeID), nNodeID);
    }

    bool cEquipment::CanDoOwnershipTransition()
    {
        if (GetStatus() != STATUS_FREE || IsDetonating() || m_bMultiplayerPickup)
            return false;
        return true;
    }

    void cEquipment::OnFailedOwnershipTransition()
    {
        Activity::cActivityManager::RetActivityManager().RequestDelete(this);
    }

    void cEquipment::SetPingedFieldStatesForNode(unsigned char nNodeID)
    {
        if (!m_bMultiplayerPickup)
            SetFieldStateForNode(nNodeID, sReplicatedField::WriteAlwaysOnce, 0);
    }

    void cEquipment::SetNetRole(etNetRole role)
    {
        Network::cNetRoleObject::SetNetRole(role);
    }

    Fun_Runtime::RetVal cEquipment::cEquipmentPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}
