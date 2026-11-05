#include "rws/classfactory.h"
#include "unknown/cHordeBeam.h"
#include "cd2/memory.h"

namespace unknown
{
    const char *cHordeBeam::RetClassName() const
    {
        return "cHordeBeam";
    }

    static RWS::CClassFactory::CRegistrar cHordeBeamRegistrar(
        "cHordeBeam", cHordeBeam::MakeNew, 0xa0, false);

    // CD2 0x82867908: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cHordeBeam::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cHordeBeam(packet);
    }
}
