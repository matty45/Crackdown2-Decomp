#include "unknown/cCrowdManager.h"
#include "rws/classfactory.h"
#include "Sim/cTimeOfDay.h"

// CD2's script registration at 0x8239B420 names the surviving RetPeriod copy.
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
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cCrowdManagerRegistrar(
        "cCrowdManager", cCrowdManager::MakeNew, 0x60, false);
}

#include "cd2/memory.h"

// CD2 0x825EC290: the class-factory constructor; the constructor stays out of line.
namespace unknown
{
    RWS::CAttributeHandler *cCrowdManager::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cCrowdManager;
    }
}
