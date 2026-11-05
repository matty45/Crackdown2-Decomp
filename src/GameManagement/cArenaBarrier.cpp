#include "rws/classfactory.h"
#include "GameManagement/cArenaBarrier.h"
#include "cd2/memory.h"

namespace GameManagement
{
    RWS::CAttributeHandler *cArenaBarrier::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cArenaBarrier;
    }

    const char *cArenaBarrier::RetClassName() const
    {
        return "cArenaBarrier";
    }

    static RWS::CClassFactory::CRegistrar cArenaBarrierRegistrar(
        "cArenaBarrier", cArenaBarrier::MakeNew, 0x20, false);
}
