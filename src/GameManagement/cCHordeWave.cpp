#include "rws/classfactory.h"
#include "GameManagement/cCHordeWave.h"
#include "cd2/memory.h"

namespace GameManagement
{
    const char *cCHordeWave::RetClassName() const
    {
        return "cCHordeWave";
    }

    static RWS::CClassFactory::CRegistrar cCHordeWaveRegistrar(
        "cCHordeWave", cCHordeWave::MakeNew, 0x238, false);

    // CD2 0x82865C98: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cCHordeWave::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cCHordeWave(packet);
    }
}
