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
#include "AI/NPCArmedBehaviour.h"
#include "AI/CellRocket.h"
#include "AI/CellRocketPrototype.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    const Fun_Runtime::cClass *CellRocket::ms_pCellRocketClass = &CellRocket::StaticCreateClass();

    const Fun_Runtime::cClass &CellRocket::RetClass() const
    {
        return *ms_pCellRocketClass;
    }

    RWS::CAttributeHandler *CellRocket::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new CellRocketPrototype(packet);
    }

    const char *CellRocket::RetClassName() const
    {
        return "CellRocket";
    }

    // CD2 0x824C3DE8: placement factory; NPCArmedBehaviour's constructor stays out of line, the rest is inlined.
    RWS::CAttributeHandler *CellRocket::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) CellRocket;
        return 0;
    }

    bool CellRocket::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pCellRocketClass->IsA(c);
    }

    void CellRocket::ChangeMainState(eState state)
    {
        m_nMainState = state;
        ChangeSubState(1);
    }

    static RWS::CClassFactory::CRegistrar CellRocketRegistrar(
        "CellRocket", CellRocket::MakeNew, 0x110, false);

    Fun_Runtime::cClass &CellRocket::StaticCreateClass()
    {
        static Fun_Runtime::cClass *CellRocketClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "CellRocket", 0x110);
        return *CellRocketClass;
    }

    // CD2 0x82F96340: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar CellRocketNPCArmedBehaviourInheritRegistrar(
        AI::CellRocket::StaticCreateClass(), AI::NPCArmedBehaviour::StaticCreateClass());

    // CD2 0x82F963F8: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar CellRocketSpawningRegistrar(
        CellRocket::StaticCreateClass(), CellRocket::SpawnFromPrototype);
}
