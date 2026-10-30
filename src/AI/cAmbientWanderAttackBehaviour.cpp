#include "AI/cAmbientWanderAttackBehaviour.h"
#include "rws/classfactory.h"

namespace AI
{
    const char *cAmbientWanderAttackBehaviour::RetClassName() const
    {
        return "cAmbientWanderAttackBehaviour";
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cAmbientWanderAttackBehaviourRegistrar(
        "cAmbientWanderAttackBehaviour", cAmbientWanderAttackBehaviour::MakeNew, 0x150, false);
}
