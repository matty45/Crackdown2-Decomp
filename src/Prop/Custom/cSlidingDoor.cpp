// src/Prop/Custom/cSlidingDoor.cpp
//
// Class: cSlidingDoor (namespace: Prop). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cSlidingDoor.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Props/Custom/cSlidingDoor.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Prop/Custom/cSlidingDoor.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "rws/classfactory.h"
#include "Prop/cSlidingDoor.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/proto_registrar.h"
#include "cd2/memory.h"
#include "fun_runtime/script_type_registrar.h"

namespace Prop
{
    const Fun_Runtime::cClass &cSlidingDoor::RetClass() const
    {
        return *ms_pcSlidingDoorClass;
    }

    bool cSlidingDoor::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcSlidingDoorClass->IsA(c);
    }

    const char *cSlidingDoor::RetClassName() const
    {
        return "cSlidingDoor";
    }

    const Fun_Runtime::cClass *cSlidingDoor::ms_pcSlidingDoorClass = &cSlidingDoor::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cSlidingDoorcPrismaticPropInheritRegistrar(
        cSlidingDoor::StaticCreateClass(), cPrismaticProp::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cSlidingDoorRegistrar(
        "cSlidingDoor", cSlidingDoor::MakeNew, 0xf00, false);

    static GOM::cProtoRegistrar cSlidingDoorSpawningRegistrar(
        cSlidingDoor::StaticCreateClass(), cSlidingDoor::SpawnFromPrototype);

    // CD2 0x827468e8: the class factory builds the prototype.
    RWS::CAttributeHandler *cSlidingDoor::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cSlidingDoorPrototype(packet);
    }

    // CD2 script-type registration names this child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cSlidingDoor> cSlidingDoorScriptRegistrar(
        "cSlidingDoor", "cPrismaticProp");

    RWS::CAttributeHandler *cSlidingDoor::SpawnFromPrototype(GOM::cObjectPrototype *prototype, void *memory)
    {
        if (memory)
            return new (memory) cSlidingDoor(prototype);
        return 0;
    }

    Fun_Runtime::cClass &cSlidingDoor::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cSlidingDoorClass = new Fun_Runtime::cClass(0x13882, "cSlidingDoor", 0xF00);
        return *cSlidingDoorClass;
    }

    // RetSTATE_Min's body (0x82381100) lies in the order-list region, outside this object's range.
    inline Fun_Runtime::State *cSlidingDoor::StaticRetSTATE_Min()
    {
        static STATE_Min s_State;
        return &s_State;
    }

    Fun_Runtime::State *cSlidingDoor::RetSTATE_Min() const
    {
        return StaticRetSTATE_Min();
    }

    Fun_Runtime::State *cSlidingDoor::RetSTATE_Min()
    {
        return StaticRetSTATE_Min();
    }

    inline Fun_Runtime::State *cSlidingDoor::StaticRetSTATE_Max()
    {
        static STATE_Max s_State;
        return &s_State;
    }

    Fun_Runtime::State *cSlidingDoor::RetSTATE_Max() const
    {
        return StaticRetSTATE_Max();
    }

    Fun_Runtime::State *cSlidingDoor::RetSTATE_Max()
    {
        return StaticRetSTATE_Max();
    }

    cSlidingDoor::cSlidingDoor(GOM::cObjectPrototype *pPrototype) : cPrismaticProp(pPrototype)
    {
    }

    cSlidingDoor::~cSlidingDoor()
    {
    }

    bool cSlidingDoor::CreatePathObject()
    {
        if (cPathObjectOwner::CreatePathObject())
        {
            InitStreamingGraphs(RetScriptPosition());
            return true;
        }
        return false;
    }

    void cSlidingDoor::DestroyPathObject()
    {
        if (m_pPathObject)
        {
            TermStreamingGraphs();
            cPathObjectOwner::DestroyPathObject();
        }
    }

    void cSlidingDoor::OnEnterGraph(AI::cStreamingGraph *pStreamingGraph)
    {
        LinkIntersectingGraphEdges(pStreamingGraph, this);
    }

    void cSlidingDoor::OnFinishedSlidingToMin()
    {
        if (m_PropAudio.IsRegistered())
            m_PropAudio.OneShot(Audio::eOSE_Training_GateClosed);
    }

    Fun_Runtime::RetVal cSlidingDoor::cSlidingDoorPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }

    void cSlidingDoor::STATE_Min::EnterPhysicalState(Fun_Runtime::cStateMachine *pSM)
    {
        static_cast<cSlidingDoor *>(pSM)->ForceToMin();
        static_cast<cSlidingDoor *>(pSM)->CreatePathObject();
    }

    void cSlidingDoor::STATE_Min::LeavePhysicalState(Fun_Runtime::cStateMachine *pSM)
    {
        static_cast<cSlidingDoor *>(pSM)->DestroyPathObject();
    }

    void cSlidingDoor::STATE_Max::EnterPhysicalState(Fun_Runtime::cStateMachine *pSM)
    {
        static_cast<cSlidingDoor *>(pSM)->ForceToMax();
        static_cast<cSlidingDoor *>(pSM)->CreatePathObject();
    }

    void cSlidingDoor::STATE_Max::LeavePhysicalState(Fun_Runtime::cStateMachine *pSM)
    {
        static_cast<cSlidingDoor *>(pSM)->DestroyPathObject();
    }
}
