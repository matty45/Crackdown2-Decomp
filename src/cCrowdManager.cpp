
// CD2's script registration at 0x8239B420 names the surviving RetPeriod copy.

#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "unknown/cCrowdManager.h"
#include "rws/classfactory.h"
#include "Sim/cTimeOfDay.h"
#include "cd2/memory.h"

namespace Sim
{
    float cTimeOfDay::RetPeriod()
    {
        return m_fPeriod;
    }
}

namespace unknown
{
    const char *cCrowdManager::RetClassName() const
    {
        return "cCrowdManager";
    }

    static RWS::CClassFactory::CRegistrar cCrowdManagerRegistrar(
        "cCrowdManager", cCrowdManager::MakeNew, 0x60, false);

    // CD2 0x825EC290: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cCrowdManager::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cCrowdManager;
    }
}
