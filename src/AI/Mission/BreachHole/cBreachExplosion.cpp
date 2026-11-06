#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/cBreachExplosion.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace AI
{
    const char *cBreachExplosion::RetClassName() const
    {
        return "cBreachExplosion";
    }

    static RWS::CClassFactory::CRegistrar cBreachExplosionRegistrar(
        "cBreachExplosion", cBreachExplosion::MakeNew, 0x90, false);

    // CD2 0x82470E88: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cBreachExplosion::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cBreachExplosion;
    }
}
