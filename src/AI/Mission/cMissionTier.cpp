#include "AI/cMissionTier.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cMissionTier::ms_pcMissionTierClass = 0;

    cMissionTier::cMissionTier() {}

    const Fun_Runtime::cClass &cMissionTier::RetClass() const
    {
        return *ms_pcMissionTierClass;
    }

    const char *cMissionTier::RetClassName() const
    {
        return "cMissionTier";
    }

    bool cMissionTier::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcMissionTierClass->IsA(c);
    }

    RWS::CAttributeHandler *cMissionTier::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cMissionTier();
    }
}

static RWS::CClassFactory::CRegistrar cMissionTierRegistrar(
    "cMissionTier", AI::cMissionTier::MakeNew, 0x7C, false);
