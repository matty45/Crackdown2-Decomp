#include "PHYSICS/cRigidBodyProfile.h"
#include "rws/classfactory.h"

namespace PHYSICS
{
    const char *cRigidBodyProfile::RetClassName() const
    {
        return "cRigidBodyProfile";
    }
}

namespace PHYSICS
{
    static RWS::CClassFactory::CRegistrar cRigidBodyProfileRegistrar(
        "cRigidBodyProfile", cRigidBodyProfile::MakeNew, 0x300, false);
}
