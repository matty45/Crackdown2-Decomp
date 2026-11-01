#include "rws/classfactory.h"
#include "GameManagement/cCHordeWave.h"

namespace GameManagement
{
    const char *cCHordeWave::RetClassName() const
    {
        return "cCHordeWave";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cCHordeWaveRegistrar(
        "cCHordeWave", cCHordeWave::MakeNew, 0x238, false);
}
