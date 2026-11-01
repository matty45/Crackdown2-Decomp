#include "rws/classfactory.h"
#include "unknown/cHordeBeam.h"

namespace unknown
{
    const char *cHordeBeam::RetClassName() const
    {
        return "cHordeBeam";
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cHordeBeamRegistrar(
        "cHordeBeam", cHordeBeam::MakeNew, 0xa0, false);
}
