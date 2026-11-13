// src/Prop/Constrained/cPrismaticProp.cpp
//
// Class: cPrismaticProp (namespace: Prop). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cPrismaticProp.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Props/Constrained/cPrismaticProp.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Prop/Constrained/cPrismaticProp.cpp

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
#include <new>
#include "rws/classfactory.h"
#include "Prop/cPrismaticProp.h"
#include "cd2/memory.h"
#include "fun_runtime/script_type_registrar.h"
#include "fun_runtime/member_script_method.h"
#include "fun_runtime/pointer_list_impl.h"

namespace Prop
{
    RWS::CAttributeHandler *cPrismaticProp::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cPrismaticPropPrototype(packet);
    }

    const char *cPrismaticProp::RetClassName() const
    {
        return "cPrismaticProp";
    }

    // CD2 0x8273BC98 has no derived cleanup beyond vtable restoration.
    cPrismaticProp::~cPrismaticProp()
    {
    }

    Fun_Runtime::cClass &cPrismaticProp::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cPrismaticPropClass = new Fun_Runtime::cClass(0x101E, "cPrismaticProp", 0xED0);
        return *cPrismaticPropClass;
    }

    const Fun_Runtime::cClass *cPrismaticProp::ms_pcPrismaticPropClass = &cPrismaticProp::StaticCreateClass();

    static RWS::CClassFactory::CRegistrar cPrismaticPropRegistrar(
        "cPrismaticProp", cPrismaticProp::MakeNew, 0xED0, false);

    RWS::CAttributeHandler *cPrismaticProp::SpawnFromPrototype(GOM::cObjectPrototype *prototype, void *memory)
    {
        if (memory)
            return new (memory) cPrismaticProp(prototype);
        return 0;
    }

}

namespace Fun_Runtime
{
    template <>
    void cScriptTypeRegistrar<Prop::cPrismaticProp>::RegisterMethods()
    {
        RegisterMethod(&Prop::cPrismaticProp::SlideToMax, "SlideToMax");
        RegisterMethod(&Prop::cPrismaticProp::SlideToMin, "SlideToMin");
        RegisterMethod(&Prop::cPrismaticProp::SlideFree, "SlideFree");
        RegisterMethod(&Prop::cPrismaticProp::IsInMinState, "IsInMinState");
        RegisterMethod(&Prop::cPrismaticProp::IsInMaxState, "IsInMaxState");
        RegisterMethod(&Prop::cPrismaticProp::IsInSlidingToMinState, "IsInSlidingToMinState");
        RegisterMethod(&Prop::cPrismaticProp::IsInSlidingToMaxState, "IsInSlidingToMaxState");
        RegisterMethod(&Prop::cPrismaticProp::IsInSlidingFreeState, "IsInSlidingFreeState");
        RegisterMethod(&Prop::cPrismaticProp::IsInBrokenOffState, "IsInBrokenOffState");
    }
}

namespace Prop
{
    inline Fun_Runtime::State *cPrismaticProp::StaticRetSTATE_Min()
    {
        static STATE_Min s_State;
        return &s_State;
    }

    Fun_Runtime::State *cPrismaticProp::RetSTATE_Min()
    {
        return StaticRetSTATE_Min();
    }

    Fun_Runtime::State *cPrismaticProp::RetSTATE_Min() const
    {
        return StaticRetSTATE_Min();
    }

    inline Fun_Runtime::State *cPrismaticProp::StaticRetSTATE_Max()
    {
        static STATE_Max s_State;
        return &s_State;
    }

    Fun_Runtime::State *cPrismaticProp::RetSTATE_Max()
    {
        return StaticRetSTATE_Max();
    }

    Fun_Runtime::State *cPrismaticProp::RetSTATE_Max() const
    {
        return StaticRetSTATE_Max();
    }

    inline Fun_Runtime::State *cPrismaticProp::StaticRetSTATE_Sliding_To_Min()
    {
        static STATE_Sliding_To_Min s_State;
        return &s_State;
    }

    Fun_Runtime::State *cPrismaticProp::RetSTATE_Sliding_To_Min()
    {
        return StaticRetSTATE_Sliding_To_Min();
    }

    Fun_Runtime::State *cPrismaticProp::RetSTATE_Sliding_To_Min() const
    {
        return StaticRetSTATE_Sliding_To_Min();
    }

    inline Fun_Runtime::State *cPrismaticProp::StaticRetSTATE_Sliding_To_Max()
    {
        static STATE_Sliding_To_Max s_State;
        return &s_State;
    }

    Fun_Runtime::State *cPrismaticProp::RetSTATE_Sliding_To_Max()
    {
        return StaticRetSTATE_Sliding_To_Max();
    }

    Fun_Runtime::State *cPrismaticProp::RetSTATE_Sliding_To_Max() const
    {
        return StaticRetSTATE_Sliding_To_Max();
    }

    inline Fun_Runtime::State *cPrismaticProp::StaticRetSTATE_Sliding_Free()
    {
        static STATE_Sliding_Free s_State;
        return &s_State;
    }

    Fun_Runtime::State *cPrismaticProp::RetSTATE_Sliding_Free()
    {
        return StaticRetSTATE_Sliding_Free();
    }

    Fun_Runtime::State *cPrismaticProp::RetSTATE_Sliding_Free() const
    {
        return StaticRetSTATE_Sliding_Free();
    }

    inline Fun_Runtime::State *cPrismaticProp::StaticRetSTATE_Broken_Off()
    {
        static STATE_Broken_Off s_State;
        return &s_State;
    }

    Fun_Runtime::State *cPrismaticProp::RetSTATE_Broken_Off()
    {
        return StaticRetSTATE_Broken_Off();
    }

    Fun_Runtime::State *cPrismaticProp::RetSTATE_Broken_Off() const
    {
        return StaticRetSTATE_Broken_Off();
    }

    // CD2 0x82FF81C0: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cPrismaticPropcPivotBasedPropInheritRegistrar(
        Prop::cPrismaticProp::StaticCreateClass(), Prop::cPivotBasedProp::StaticCreateClass());

    // CD2 0x82FF8278: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cPrismaticPropSpawningRegistrar(
        cPrismaticProp::StaticCreateClass(), cPrismaticProp::SpawnFromPrototype);

    // CD2 script-type registration; constructor/table evidence identifies the child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cPrismaticProp> cPrismaticPropScriptRegistrar(
        "cPrismaticProp", "cProp");
}
