#include "rws/classfactory.h"
#include "GameManagement/cArenaBarrier.h"

namespace GameManagement
{
    const char *cArenaBarrier::RetClassName() const
    {
        return "cArenaBarrier";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cArenaBarrierRegistrar(
        "cArenaBarrier", cArenaBarrier::MakeNew, 0x20, false);
}
