#include "cd2/memory.h"
#include "gom/proto_registrar.h"
#include "AI/CellGuard.h"
#include "rws/classfactory.h"

namespace AI
{
    const char *CellGuard::RetClassName() const
    {
        return "CellGuard";
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar CellGuardRegistrar(
        "CellGuard", CellGuard::MakeNew, 0x1A0, false);
}

// CD2 0x82F95B88: class descriptor and placement factory.
namespace AI
{
    static GOM::cProtoRegistrar CellGuardSpawningRegistrar(
        CellGuard::StaticCreateClass(), CellGuard::SpawnFromPrototype);
}

namespace AI
{
    RWS::CAttributeHandler *CellGuard::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) CellGuard;
        return 0;
    }
}

namespace AI
{
    const Fun_Runtime::cClass &CellGuard::RetClass() const
    {
        return *ms_pcCellGuardClass;
    }
}
