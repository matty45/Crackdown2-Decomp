#include "rws/classfactory.h"
#include "GameManagement/cNetGamePlayerSpawnPoint.h"
#include "rws/time.h"
#include "cd2/memory.h"

namespace GameManagement
{
    RWS::CAttributeHandler *cNetGamePlayerSpawnPoint::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cNetGamePlayerSpawnPoint;
    }

    void cNetGamePlayerSpawnPoint::SetInactive(unsigned int nDuration)
    {
        m_nReactivateTime = RWS::Time::RetGameTime() + nDuration;
    }

    bool cNetGamePlayerSpawnPoint::IsActive() const
    {
        return RWS::Time::RetGameTime() >= m_nReactivateTime;
    }

    const char *cNetGamePlayerSpawnPoint::RetClassName() const
    {
        return "cNetGamePlayerSpawnPoint";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cNetGamePlayerSpawnPointRegistrar(
        "cNetGamePlayerSpawnPoint", cNetGamePlayerSpawnPoint::MakeNew, 0x90, false);
}
