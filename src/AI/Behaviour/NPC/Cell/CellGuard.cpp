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
