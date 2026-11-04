#include "fun_runtime/inheritance_registrar.h"
#include "AI/NPCArmedBehaviour.h"
#include "AI/CellRocket.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *CellRocket::ms_pCellRocketClass = &CellRocket::StaticCreateClass();


    const Fun_Runtime::cClass &CellRocket::RetClass() const
    {
        return *ms_pCellRocketClass;
    }

    const char *CellRocket::RetClassName() const
    {
        return "CellRocket";
    }

    bool CellRocket::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pCellRocketClass->IsA(c);
    }

    RWS::CAttributeHandler *CellRocket::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new CellRocket();
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar CellRocketRegistrar(
        "CellRocket", CellRocket::MakeNew, 0x110, false);
}

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &CellRocket::StaticCreateClass()
    {
        static Fun_Runtime::cClass *CellRocketClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "CellRocket", 0x110);
        return *CellRocketClass;
    }
}

// CD2 0x82F96340: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar CellRocketNPCArmedBehaviourInheritRegistrar(
        AI::CellRocket::StaticCreateClass(), AI::NPCArmedBehaviour::StaticCreateClass());
}

#include <new>

// CD2 0x824C3DE8: placement factory; NPCArmedBehaviour's constructor stays out of line, the rest is inlined.
namespace AI
{
    RWS::CAttributeHandler *CellRocket::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) CellRocket;
        return 0;
    }
}

#include "gom/proto_registrar.h"

// CD2 0x82F963F8: the spawning registrar (GOM::cProtoRegistrar constructor 0x82657690) pairs the runtime class with
// its placement factory.
namespace AI
{
    static GOM::cProtoRegistrar CellRocketSpawningRegistrar(
        CellRocket::StaticCreateClass(), CellRocket::SpawnFromPrototype);
}
