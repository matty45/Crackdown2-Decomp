#include "rws/classfactory.h"
#include "GameManagement/cTrainingRespawnPoint.h"

namespace GameManagement
{
    const char *cTrainingRespawnPoint::RetClassName() const
    {
        return "cTrainingRespawnPoint";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cTrainingRespawnPointRegistrar(
        "cTrainingRespawnPoint", cTrainingRespawnPoint::MakeNew, 0x80, false);
}

#include "cd2/memory.h"

// CD2 0x828586C0: the class-factory constructor; the constructor stays out of line.
namespace GameManagement
{
    RWS::CAttributeHandler *cTrainingRespawnPoint::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cTrainingRespawnPoint(packet);
    }
}
