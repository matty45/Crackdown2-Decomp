#include "rws/classfactory.h"
#include "GameManagement/cCD1Barrier.h"

namespace GameManagement
{
    const char *cCD1Barrier::RetClassName() const
    {
        return "cCD1Barrier";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cCD1BarrierRegistrar(
        "cCD1Barrier", cCD1Barrier::MakeNew, 0x60, false);
}
