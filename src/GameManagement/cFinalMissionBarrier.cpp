#include "rws/classfactory.h"
#include "GameManagement/cFinalMissionBarrier.h"

namespace GameManagement
{
    const char *cFinalMissionBarrier::RetClassName() const
    {
        return "cFinalMissionBarrier";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cFinalMissionBarrierRegistrar(
        "cFinalMissionBarrier", cFinalMissionBarrier::MakeNew, 0x80, false);
}
