#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "unknown/cRenegadesProfile.h"

namespace unknown
{
    const char *cRenegadesProfile::RetClassName() const
    {
        return "cRenegadesProfile";
    }

    static RWS::CClassFactory::CRegistrar cRenegadesProfileRegistrar(
        "cRenegadesProfile", cRenegadesProfile::MakeNew, 0x40, false);
}
