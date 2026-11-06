#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "unknown/cLaunchPadConfig.h"
#include "rws/classfactory.h"

namespace unknown
{
    const char *cLaunchPadConfig::RetClassName() const
    {
        return "cLaunchPadConfig";
    }

    RWS::CAttributeHandler *cLaunchPadConfig::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        cLaunchPadConfig *p = new cLaunchPadConfig();
        return p;
    }

    static RWS::CClassFactory::CRegistrar cLaunchPadConfigRegistrar(
        "cLaunchPadConfig", cLaunchPadConfig::MakeNew, 0x18, false);
}
