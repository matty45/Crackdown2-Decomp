// src/Prop/Constrained/cHingedProp.cpp
//
// Class: cHingedProp (namespace: Prop). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cHingedProp.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Props/Constrained/cHingedProp.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Prop/Constrained/cHingedProp.cpp

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
#include "Prop/cPivotBasedProp.h"
#include "rws/classfactory.h"
#include "Prop/cHingedProp.h"
#include <new>
#include "cd2/memory.h"
#include "fun_runtime/script_type_registrar.h"
#include "fun_runtime/member_script_method.h"
#include "fun_runtime/pointer_list_impl.h"
#include "AI/cHingedPropRotatedToMinEvent.h"
#include "AI/cHingedPropRotatedToMaxEvent.h"

namespace Prop
{
    const Fun_Runtime::cClass &cHingedProp::RetClass() const
    {
        return *ms_pcHingedPropClass;
    }

    bool cHingedProp::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcHingedPropClass->IsA(c);
    }

    RWS::CAttributeHandler *cHingedProp::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cHingedPropPrototype(packet);
    }

    const char *cHingedProp::RetClassName() const
    {
        return "cHingedProp";
    }

    // CD2 0x82737698 has no derived cleanup beyond vtable restoration.
    cHingedProp::~cHingedProp()
    {
    }

}

// These AI event getters lie between the prop's methods in CD2's split.
namespace AI
{
    const Fun_Runtime::cScriptTypeRegistration *cHingedPropRotatedToMinEvent::RetScriptTypeRegistration() const
    {
        return &g_cHingedPropRotatedToMinEvent;
    }

    const Fun_Runtime::cScriptTypeRegistration *cHingedPropRotatedToMaxEvent::RetScriptTypeRegistration() const
    {
        return &g_cHingedPropRotatedToMaxEvent;
    }
}

namespace Prop
{
    Fun_Runtime::cClass &cHingedProp::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cHingedPropClass = new Fun_Runtime::cClass(0x101D, "cHingedProp", 0xEB0);
        return *cHingedPropClass;
    }

    const Fun_Runtime::cClass *cHingedProp::ms_pcHingedPropClass = &cHingedProp::StaticCreateClass();

    static RWS::CClassFactory::CRegistrar cHingedPropRegistrar(
        "cHingedProp", cHingedProp::MakeNew, 0xEB0, false);

    RWS::CAttributeHandler *cHingedProp::SpawnFromPrototype(GOM::cObjectPrototype *prototype, void *memory)
    {
        if (memory)
            return new (memory) cHingedProp(prototype);
        return 0;
    }

}

namespace Fun_Runtime
{
    template <>
    void cScriptTypeRegistrar<Prop::cHingedProp>::RegisterMethods()
    {
        RegisterMethod(&Prop::cHingedProp::RotToMax, "RotToMax");
        RegisterMethod(&Prop::cHingedProp::RotToMin, "RotToMin");
        RegisterMethod(&Prop::cHingedProp::RotFree, "RotFree");
        RegisterMethod(&Prop::cHingedProp::DingDong, "DingDong");
        RegisterMethod(&Prop::cHingedProp::IsInMinState, "IsInMinState");
        RegisterMethod(&Prop::cHingedProp::IsInMaxState, "IsInMaxState");
        RegisterMethod(&Prop::cHingedProp::IsInRotatingToMinState, "IsInRotatingToMinState");
        RegisterMethod(&Prop::cHingedProp::IsInRotatingToMaxState, "IsInRotatingToMaxState");
        RegisterMethod(&Prop::cHingedProp::IsInRotatingFreeState, "IsInRotatingFreeState");
        RegisterMethod(&Prop::cHingedProp::IsInBrokenOffState, "IsInBrokenOffState");
    }
}

namespace Prop
{
    inline Fun_Runtime::State *cHingedProp::StaticRetSTATE_Min()
    {
        static STATE_Min s_State;
        return &s_State;
    }

    Fun_Runtime::State *cHingedProp::RetSTATE_Min() const
    {
        return StaticRetSTATE_Min();
    }

    Fun_Runtime::State *cHingedProp::RetSTATE_Min()
    {
        return StaticRetSTATE_Min();
    }

    inline Fun_Runtime::State *cHingedProp::StaticRetSTATE_Max()
    {
        static STATE_Max s_State;
        return &s_State;
    }

    Fun_Runtime::State *cHingedProp::RetSTATE_Max() const
    {
        return StaticRetSTATE_Max();
    }

    Fun_Runtime::State *cHingedProp::RetSTATE_Max()
    {
        return StaticRetSTATE_Max();
    }

    inline Fun_Runtime::State *cHingedProp::StaticRetSTATE_Rotating_To_Min()
    {
        static STATE_Rotating_To_Min s_State;
        return &s_State;
    }

    Fun_Runtime::State *cHingedProp::RetSTATE_Rotating_To_Min() const
    {
        return StaticRetSTATE_Rotating_To_Min();
    }

    Fun_Runtime::State *cHingedProp::RetSTATE_Rotating_To_Min()
    {
        return StaticRetSTATE_Rotating_To_Min();
    }

    inline Fun_Runtime::State *cHingedProp::StaticRetSTATE_Rotating_To_Max()
    {
        static STATE_Rotating_To_Max s_State;
        return &s_State;
    }

    Fun_Runtime::State *cHingedProp::RetSTATE_Rotating_To_Max() const
    {
        return StaticRetSTATE_Rotating_To_Max();
    }

    Fun_Runtime::State *cHingedProp::RetSTATE_Rotating_To_Max()
    {
        return StaticRetSTATE_Rotating_To_Max();
    }

    inline Fun_Runtime::State *cHingedProp::StaticRetSTATE_Rotating_Free()
    {
        static STATE_Rotating_Free s_State;
        return &s_State;
    }

    Fun_Runtime::State *cHingedProp::RetSTATE_Rotating_Free() const
    {
        return StaticRetSTATE_Rotating_Free();
    }

    Fun_Runtime::State *cHingedProp::RetSTATE_Rotating_Free()
    {
        return StaticRetSTATE_Rotating_Free();
    }

    inline Fun_Runtime::State *cHingedProp::StaticRetSTATE_Broken_Off()
    {
        static STATE_Broken_Off s_State;
        return &s_State;
    }

    Fun_Runtime::State *cHingedProp::RetSTATE_Broken_Off() const
    {
        return StaticRetSTATE_Broken_Off();
    }

    Fun_Runtime::State *cHingedProp::RetSTATE_Broken_Off()
    {
        return StaticRetSTATE_Broken_Off();
    }

    // CD2 0x82FF70D0: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cHingedPropcPivotBasedPropInheritRegistrar(
        Prop::cHingedProp::StaticCreateClass(), Prop::cPivotBasedProp::StaticCreateClass());

    // CD2 0x82FF7188: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cHingedPropSpawningRegistrar(
        cHingedProp::StaticCreateClass(), cHingedProp::SpawnFromPrototype);

    // CD2 script-type registration; constructor/table evidence identifies the child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cHingedProp> cHingedPropScriptRegistrar(
        "cHingedProp", "cProp");

    const Fun_Runtime::cScriptTypeRegistration *cHingedProp::RetScriptTypeRegistration() const
    {
        return &cHingedPropScriptRegistrar;
    }

    void cHingedProp::GoToInitialState()
    {
        if (static_cast<cPropPrototype *>(m_pPrototype)->m_nMotionType == eMT_DYNAMIC)
            GoToBrokenOffState();
        else
            GoToMinState();
    }

    void cHingedProp::RotToMax()
    {
        if (IsInMinState() || IsInRotatingToMinState() || IsInRotatingFreeState())
            GoToRotatingToMaxState();
    }

    void cHingedProp::RotToMin()
    {
        if (IsInMaxState() || IsInRotatingToMaxState() || IsInRotatingFreeState())
            GoToRotatingToMinState();
    }

    void cHingedProp::RotFree()
    {
        if (IsInMaxState() || IsInMinState() || IsInRotatingToMaxState() || IsInRotatingToMinState())
            GoToRotatingFreeState();
        m_bDoDingDong = false;
    }

    void cHingedProp::DingDong()
    {
        m_bDoDingDong = true;
        RotToMax();
    }

    void cHingedProp::Breakoff(bool force)
    {
        if (force || RetPropPrototype()->m_nMotionType != eMT_FIXED)
            GoToBrokenOffState();
    }

    void cHingedProp::EnterGhostState()
    {
        GoToBrokenOffState();
        cProp::EnterGhostState();
    }

    void cHingedProp::OnSpawnedAsFragment(cGameBase *parent)
    {
        cProp::OnSpawnedAsFragment(parent);
        GoToBrokenOffState();
    }

    Fun_Runtime::RetVal cHingedProp::cHingedPropPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }

    void cHingedProp::STATE_Min::EnterPhysicalState(Fun_Runtime::cStateMachine *machine)
    {
        static_cast<cHingedProp *>(machine)->ForceToMin();
    }

    void cHingedProp::STATE_Max::EnterPhysicalState(Fun_Runtime::cStateMachine *machine)
    {
        static_cast<cHingedProp *>(machine)->ForceToMax();
    }

    void cHingedProp::STATE_Rotating_To_Min::EnterPhysicalState(Fun_Runtime::cStateMachine *machine)
    {
        cHingedProp *prop = static_cast<cHingedProp *>(machine);
        prop->CreateConstraint(true, static_cast<cHingedPropPrototype *>(prop->m_pPrototype)->m_fMinAngle);
    }

    void cHingedProp::STATE_Rotating_To_Max::EnterPhysicalState(Fun_Runtime::cStateMachine *machine)
    {
        cHingedProp *prop = static_cast<cHingedProp *>(machine);
        prop->CreateConstraint(true, static_cast<cHingedPropPrototype *>(prop->m_pPrototype)->m_fMaxAngle);
    }

    void cHingedProp::STATE_Rotating_Free::LeavePhysicalState(Fun_Runtime::cStateMachine *machine)
    {
        static_cast<cHingedProp *>(machine)->DestroyConstraint();
    }

    void cHingedProp::STATE_Broken_Off::BeginState(Fun_Runtime::cStateMachine *machine)
    {
        cHingedProp *prop = static_cast<cHingedProp *>(machine);
        prop->SetMotion(eMT_DYNAMIC);
        prop->vf338();
    }
}
