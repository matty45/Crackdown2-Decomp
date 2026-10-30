#include "AI/cMissionActivationCylinder.h"
#include "rws/classfactory.h"

namespace AI
{
    const char *cMissionActivationCylinder::RetClassName() const
    {
        return "cMissionActivationCylinder";
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cMissionActivationCylinderRegistrar(
        "cMissionActivationCylinder", cMissionActivationCylinder::MakeNew, 0x110, false);
}
