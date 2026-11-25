// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Prop/cHingedProp.h"
#include "Prop/cHingedDoor.h"
#include <new>
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "fun_runtime/script_type_registrar.h"

namespace Prop
{
    const Fun_Runtime::cClass &cHingedDoor::RetClass() const
    {
        return *ms_pcHingedDoorClass;
    }

    bool cHingedDoor::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcHingedDoorClass->IsA(c);
    }

    RWS::CAttributeHandler *cHingedDoor::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cHingedDoorPrototype(packet);
    }

    const char *cHingedDoor::RetClassName() const
    {
        return "cHingedDoor";
    }

    static RWS::CClassFactory::CRegistrar cHingedDoorRegistrar(
        "cHingedDoor", cHingedDoor::MakeNew, 0xEE0, false);

    Fun_Runtime::cClass &cHingedDoor::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cHingedDoorClass = new Fun_Runtime::cClass(0x13881, "cHingedDoor", 0xEE0);
        return *cHingedDoorClass;
    }

    inline Fun_Runtime::State *cHingedDoor::StaticRetSTATE_Min()
    {
        static STATE_Min s_State;
        return &s_State;
    }

    Fun_Runtime::State *cHingedDoor::RetSTATE_Min() const
    {
        return StaticRetSTATE_Min();
    }

    Fun_Runtime::State *cHingedDoor::RetSTATE_Min()
    {
        return StaticRetSTATE_Min();
    }

    inline Fun_Runtime::State *cHingedDoor::StaticRetSTATE_Max()
    {
        static STATE_Max s_State;
        return &s_State;
    }

    Fun_Runtime::State *cHingedDoor::RetSTATE_Max() const
    {
        return StaticRetSTATE_Max();
    }

    Fun_Runtime::State *cHingedDoor::RetSTATE_Max()
    {
        return StaticRetSTATE_Max();
    }

    cHingedDoor::cHingedDoor(GOM::cObjectPrototype *pPrototype) : cHingedProp(pPrototype)
    {
    }

    cHingedDoor::~cHingedDoor()
    {
    }

    void cHingedDoor::TickUpdate(float dt)
    {
        cHingedProp::TickUpdate(dt);
    }

    bool cHingedDoor::CreatePathObject()
    {
        if (cPathObjectOwner::CreatePathObject())
        {
            InitStreamingGraphs(RetScriptPosition());
            return true;
        }
        return false;
    }

    void cHingedDoor::OnEnterGraph(AI::cStreamingGraph *pStreamingGraph)
    {
        LinkIntersectingGraphEdges(pStreamingGraph, this);
    }

    void cHingedDoor::STATE_Min::EnterPhysicalState(Fun_Runtime::cStateMachine *pSM)
    {
        static_cast<cHingedDoor *>(pSM)->ForceToMin();
        static_cast<cHingedDoor *>(pSM)->CreatePathObject();
    }

    void cHingedDoor::STATE_Min::LeavePhysicalState(Fun_Runtime::cStateMachine *pSM)
    {
        static_cast<cHingedDoor *>(pSM)->DestroyPathObject();
    }

    void cHingedDoor::STATE_Max::EnterPhysicalState(Fun_Runtime::cStateMachine *pSM)
    {
        static_cast<cHingedDoor *>(pSM)->ForceToMax();
        static_cast<cHingedDoor *>(pSM)->CreatePathObject();
    }

    void cHingedDoor::STATE_Max::LeavePhysicalState(Fun_Runtime::cStateMachine *pSM)
    {
        static_cast<cHingedDoor *>(pSM)->DestroyPathObject();
    }

    const Fun_Runtime::cClass *cHingedDoor::ms_pcHingedDoorClass = &cHingedDoor::StaticCreateClass();

    // CD2 0x82FFAEF0: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cHingedDoorcHingedPropInheritRegistrar(
        Prop::cHingedDoor::StaticCreateClass(), Prop::cHingedProp::StaticCreateClass());

    // CD2 0x82FFAFA8: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cHingedDoorSpawningRegistrar(
        cHingedDoor::StaticCreateClass(), cHingedDoor::SpawnFromPrototype);

    // CD2 script-type registration; constructor/table evidence identifies the child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cHingedDoor> cHingedDoorScriptRegistrar(
        "cHingedDoor", "cHingedProp");

    RWS::CAttributeHandler *cHingedDoor::SpawnFromPrototype(GOM::cObjectPrototype *pPrototype, void *pMem)
    {
        if (pMem)
            return new (pMem) cHingedDoor(pPrototype);
        return 0;
    }

    const Fun_Runtime::cScriptTypeRegistration *cHingedDoor::RetScriptTypeRegistration() const
    {
        return &cHingedDoorScriptRegistrar;
    }

    Fun_Runtime::RetVal cHingedDoor::cHingedDoorPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}
