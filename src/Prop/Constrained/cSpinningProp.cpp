// src/Prop/Constrained/cSpinningProp.cpp
//
// Class: cSpinningProp (namespace: Prop). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cSpinningProp.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Props/Constrained/cSpinningProp.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Prop/Constrained/cSpinningProp.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Prop/cPivotBasedProp.h"
#include <new>
#include "rws/classfactory.h"
#include "Prop/cSpinningProp.h"
#include "cd2/memory.h"
#include "fun_runtime/script_type_registrar.h"
#include "fun_runtime/member_script_method.h"
#include "fun_runtime/pointer_list_impl.h"

namespace Prop
{
    RWS::CAttributeHandler *cSpinningProp::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cSpinningPropPrototype(packet);
    }

    const char *cSpinningProp::RetClassName() const
    {
        return "cSpinningProp";
    }

    RWS::CAttributeHandler *cSpinningProp::SpawnFromPrototype(GOM::cObjectPrototype *prototype, void *memory)
    {
        if (memory)
            return new (memory) cSpinningProp(prototype);
        return 0;
    }

    Fun_Runtime::cClass &cSpinningProp::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cSpinningPropClass = new Fun_Runtime::cClass(0x101C, "cSpinningProp", 0xE50);
        return *cSpinningPropClass;
    }

}

namespace Fun_Runtime
{
    template <>
    void cScriptTypeRegistrar<Prop::cSpinningProp>::RegisterMethods()
    {
        RegisterMethod(&Prop::cSpinningProp::SpinClockWise, "SpinClockWise");
        RegisterMethod(&Prop::cSpinningProp::SpinAntiClockWise, "SpinAntiClockWise");
        RegisterMethod(&Prop::cSpinningProp::SpinFree, "SpinFree");
        RegisterMethod(&Prop::cSpinningProp::IsInSpinningClockWiseState, "IsInSpinningClockWiseState");
        RegisterMethod(&Prop::cSpinningProp::IsInSpinningAntiClockWiseState, "IsInSpinningAntiClockWiseState");
        RegisterMethod(&Prop::cSpinningProp::IsInSpinningFreeState, "IsInSpinningFreeState");
        RegisterMethod(&Prop::cSpinningProp::IsInBrokenOffState, "IsInBrokenOffState");
    }
}

namespace Prop
{
    inline Fun_Runtime::State *cSpinningProp::StaticRetSTATE_Spinning_ClockWise()
    {
        static STATE_Spinning_ClockWise s_State;
        return &s_State;
    }

    Fun_Runtime::State *cSpinningProp::RetSTATE_Spinning_ClockWise() const
    {
        return StaticRetSTATE_Spinning_ClockWise();
    }

    Fun_Runtime::State *cSpinningProp::RetSTATE_Spinning_ClockWise()
    {
        return StaticRetSTATE_Spinning_ClockWise();
    }

    inline Fun_Runtime::State *cSpinningProp::StaticRetSTATE_Spinning_AntiClockWise()
    {
        static STATE_Spinning_AntiClockWise s_State;
        return &s_State;
    }

    Fun_Runtime::State *cSpinningProp::RetSTATE_Spinning_AntiClockWise() const
    {
        return StaticRetSTATE_Spinning_AntiClockWise();
    }

    Fun_Runtime::State *cSpinningProp::RetSTATE_Spinning_AntiClockWise()
    {
        return StaticRetSTATE_Spinning_AntiClockWise();
    }

    inline Fun_Runtime::State *cSpinningProp::StaticRetSTATE_Spinning_Free()
    {
        static STATE_Spinning_Free s_State;
        return &s_State;
    }

    Fun_Runtime::State *cSpinningProp::RetSTATE_Spinning_Free() const
    {
        return StaticRetSTATE_Spinning_Free();
    }

    Fun_Runtime::State *cSpinningProp::RetSTATE_Spinning_Free()
    {
        return StaticRetSTATE_Spinning_Free();
    }

    inline Fun_Runtime::State *cSpinningProp::StaticRetSTATE_Broken_Off()
    {
        static STATE_Broken_Off s_State;
        return &s_State;
    }

    Fun_Runtime::State *cSpinningProp::RetSTATE_Broken_Off() const
    {
        return StaticRetSTATE_Broken_Off();
    }

    Fun_Runtime::State *cSpinningProp::RetSTATE_Broken_Off()
    {
        return StaticRetSTATE_Broken_Off();
    }

    // CD2 0x8273EB20 has no derived cleanup beyond vtable restoration.
    cSpinningProp::~cSpinningProp()
    {
    }

    Fun_Runtime::RetVal cSpinningProp::Init(const GOM::cSpawner *pSpawnArgs)
    {
        Fun_Runtime::RetVal ret = cProp::Init(pSpawnArgs);
        if (CanGoToInitialState())
            GoToInitialState();
        return ret;
    }

    void cSpinningProp::GoToInitialState()
    {
        if (static_cast<cPropPrototype *>(m_pPrototype)->m_nMotionType == eMT_DYNAMIC)
            GoToBrokenOffState();
        else
            GoToSpinningClockWiseState();
    }

    void cSpinningProp::SpinClockWise()
    {
        if (IsInSpinningAntiClockWiseState() || IsInSpinningFreeState())
            GoToSpinningClockWiseState();
    }

    void cSpinningProp::SpinAntiClockWise()
    {
        if (IsInSpinningClockWiseState() || IsInSpinningFreeState())
            GoToSpinningAntiClockWiseState();
    }

    void cSpinningProp::SpinFree()
    {
        if (IsInSpinningClockWiseState() || IsInSpinningAntiClockWiseState())
            GoToSpinningFreeState();
    }

    void cSpinningProp::Breakoff(bool)
    {
        GoToBrokenOffState();
    }

    void cSpinningProp::EnterGhostState()
    {
        GoToBrokenOffState();
        cProp::EnterGhostState();
    }

    void cSpinningProp::OnSpawnedAsFragment(cGameBase *pParent)
    {
        cProp::OnSpawnedAsFragment(pParent);
        GoToBrokenOffState();
    }


    void cSpinningProp::STATE_Spinning_ClockWise::LeavePhysicalState(Fun_Runtime::cStateMachine *machine)
    {
        cSpinningProp *owner = static_cast<cSpinningProp *>(machine);
        owner->DestroyMotor();
        owner->DestroyConstraint();
    }

    void cSpinningProp::STATE_Spinning_AntiClockWise::LeavePhysicalState(Fun_Runtime::cStateMachine *machine)
    {
        cSpinningProp *owner = static_cast<cSpinningProp *>(machine);
        owner->DestroyMotor();
        owner->DestroyConstraint();
    }

    cSpinningProp::cSpinningPropPrototype::cSpinningPropPrototype(const RWS::CAttributePacket &attr)
        : cPivotBasedPropPrototype(attr), m_fSpinSpeed(Fun_Runtime::g_GlobalConstants.CONST_FLOAT_1), m_fSpinAccel(2.0f)
    {
    }

    Fun_Runtime::RetVal cSpinningProp::cSpinningPropPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }

    void cSpinningProp::STATE_Spinning_Free::EnterPhysicalState(Fun_Runtime::cStateMachine *machine)
    {
        static_cast<cSpinningProp *>(machine)->CreateConstraint();
    }

    void cSpinningProp::STATE_Spinning_Free::LeavePhysicalState(Fun_Runtime::cStateMachine *machine)
    {
        static_cast<cSpinningProp *>(machine)->DestroyConstraint();
    }

    const Fun_Runtime::cClass *cSpinningProp::ms_pcSpinningPropClass = &cSpinningProp::StaticCreateClass();

    static RWS::CClassFactory::CRegistrar cSpinningPropRegistrar(
        "cSpinningProp", cSpinningProp::MakeNew, 0xE50, false);


    // CD2 0x82FF8EF0: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cSpinningPropcPivotBasedPropInheritRegistrar(
        Prop::cSpinningProp::StaticCreateClass(), Prop::cPivotBasedProp::StaticCreateClass());

    // CD2 0x82FF8FA8: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cSpinningPropSpawningRegistrar(
        cSpinningProp::StaticCreateClass(), cSpinningProp::SpawnFromPrototype);

    // CD2 script-type registration; constructor/table evidence identifies the child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cSpinningProp> cSpinningPropScriptRegistrar(
        "cSpinningProp", "cProp");

    // The inherited state-entry policy is unconditional in this class: CD2
    // primary slot 357 shares the constant-true body used by other defaults.
    bool cSpinningProp::CanGoToInitialState() const
    {
        return true;
    }
}
