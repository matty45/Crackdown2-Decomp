#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "GameRenderer/cCD2Lighting.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace GameRenderer
{
    const char *cCD2Lighting::RetClassName() const
    {
        return "cCD2Lighting";
    }

    static RWS::CClassFactory::CRegistrar cCD2LightingRegistrar(
        "cCD2Lighting", cCD2Lighting::MakeNew, 0x2680, false);

    // CD2 0x8265A1A8: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cCD2Lighting::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cCD2Lighting;
    }
}
