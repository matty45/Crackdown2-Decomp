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

#include "cd2/memory.h"

// CD2 0x824C0B08: the class-factory constructor; the constructor stays out of line.
namespace AI
{
    RWS::CAttributeHandler *CellGuard::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new CellGuard(packet);
    }
}
