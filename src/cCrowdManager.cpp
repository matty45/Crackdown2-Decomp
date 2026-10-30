#include "unknown/cCrowdManager.h"
#include "rws/classfactory.h"

namespace unknown
{
    const char *cCrowdManager::RetClassName() const
    {
        return "cCrowdManager";
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cCrowdManagerRegistrar(
        "cCrowdManager", cCrowdManager::MakeNew, 0x60, false);
}
