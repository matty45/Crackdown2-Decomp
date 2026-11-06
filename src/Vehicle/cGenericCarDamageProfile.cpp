#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Vehicle/cGenericCarDamageProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Vehicle
{
    cGenericCarDamageProfile *cGenericCarDamageProfile::ms_pInstance;

    RWS::CAttributeHandler *cGenericCarDamageProfile::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cGenericCarDamageProfile(packet);
    }

    cGenericCarDamageProfile::~cGenericCarDamageProfile()
    {
    }

    const char *cGenericCarDamageProfile::RetClassName() const
    {
        return "cGenericCarDamageProfile";
    }

    static RWS::CClassFactory::CRegistrar cGenericCarDamageProfileRegistrar(
        "cGenericCarDamageProfile", cGenericCarDamageProfile::MakeNew, 0x5C, false);
}
