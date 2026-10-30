#include "AI/PedestrianGuard.h"
#include "rws/classfactory.h"

namespace AI
{
    const char *PedestrianGuard::RetClassName() const
    {
        return "PedestrianGuard";
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar PedestrianGuardRegistrar(
        "PedestrianGuard", PedestrianGuard::MakeNew, 0x130, false);
}
