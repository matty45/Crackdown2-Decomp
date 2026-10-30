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
