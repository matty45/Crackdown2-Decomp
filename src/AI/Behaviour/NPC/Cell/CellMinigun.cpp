#include "fun_runtime/inheritance_registrar.h"
#include "AI/NPCArmedBehaviour.h"
#include "AI/CellMinigun.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *CellMinigun::ms_pCellMinigunClass = &CellMinigun::StaticCreateClass();


    const Fun_Runtime::cClass &CellMinigun::RetClass() const
    {
        return *ms_pCellMinigunClass;
    }

    const char *CellMinigun::RetClassName() const
    {
        return "CellMinigun";
    }

    bool CellMinigun::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pCellMinigunClass->IsA(c);
    }

    RWS::CAttributeHandler *CellMinigun::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new CellMinigun();
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar CellMinigunRegistrar(
        "CellMinigun", CellMinigun::MakeNew, 0x100, false);
}

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &CellMinigun::StaticCreateClass()
    {
        static Fun_Runtime::cClass *CellMinigunClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "CellMinigun", 0x100);
        return *CellMinigunClass;
    }
}

// CD2 0x82F95F08: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar CellMinigunNPCArmedBehaviourInheritRegistrar(
        AI::CellMinigun::StaticCreateClass(), AI::NPCArmedBehaviour::StaticCreateClass());
}

#include <new>

// CD2 0x824C3228: placement factory; NPCArmedBehaviour's constructor stays out of line, the rest is inlined.
namespace AI
{
    RWS::CAttributeHandler *CellMinigun::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) CellMinigun;
        return 0;
    }
}

#include "gom/proto_registrar.h"

// CD2 0x82F95FC0: the spawning registrar (GOM::cProtoRegistrar constructor 0x82657690) pairs the runtime class with
// its placement factory.
namespace AI
{
    static GOM::cProtoRegistrar CellMinigunSpawningRegistrar(
        CellMinigun::StaticCreateClass(), CellMinigun::SpawnFromPrototype);
}
