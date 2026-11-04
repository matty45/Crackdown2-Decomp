#include "AI/cBreachExplosion.h"
#include "rws/classfactory.h"

namespace AI
{
    const char *cBreachExplosion::RetClassName() const
    {
        return "cBreachExplosion";
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cBreachExplosionRegistrar(
        "cBreachExplosion", cBreachExplosion::MakeNew, 0x90, false);
}

#include "cd2/memory.h"

// CD2 0x82470E88: the class-factory constructor; the constructor stays out of line.
namespace AI
{
    RWS::CAttributeHandler *cBreachExplosion::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cBreachExplosion;
    }
}
