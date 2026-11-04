#include "GameRenderer/cCD2Lighting.h"
#include "rws/classfactory.h"

namespace GameRenderer
{
    const char *cCD2Lighting::RetClassName() const
    {
        return "cCD2Lighting";
    }
}

namespace GameRenderer
{
    static RWS::CClassFactory::CRegistrar cCD2LightingRegistrar(
        "cCD2Lighting", cCD2Lighting::MakeNew, 0x2680, false);
}

#include "cd2/memory.h"

// CD2 0x8265A1A8: the class-factory constructor; the constructor stays out of line.
namespace GameRenderer
{
    RWS::CAttributeHandler *cCD2Lighting::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cCD2Lighting;
    }
}
