#include "cd2/memory.h"
#include "gom/proto_registrar.h"
#include "AI/Peacekeeper.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *Peacekeeper::ms_pPeacekeeperClass = 0;

    Peacekeeper::Peacekeeper() {}

    const Fun_Runtime::cClass &Peacekeeper::RetClass() const
    {
        return *ms_pPeacekeeperClass;
    }

    const char *Peacekeeper::RetClassName() const
    {
        return "Peacekeeper";
    }

    bool Peacekeeper::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pPeacekeeperClass->IsA(c);
    }

    RWS::CAttributeHandler *Peacekeeper::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new Peacekeeper();
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar PeacekeeperRegistrar(
        "Peacekeeper", Peacekeeper::MakeNew, 0x1E0, false);
}

// CD2 0x82F978A8: class descriptor and placement factory.
namespace AI
{
    static GOM::cProtoRegistrar PeacekeeperSpawningRegistrar(
        Peacekeeper::StaticCreateClass(), Peacekeeper::SpawnFromPrototype);
}

namespace AI
{
    RWS::CAttributeHandler *Peacekeeper::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) Peacekeeper;
        return 0;
    }
}
