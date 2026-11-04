#include "AI/cAgencyTowerSegmentMission.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cAgencyTowerSegmentMission::ms_pcAgencyTowerSegmentMissionClass = &cAgencyTowerSegmentMission::StaticCreateClass();

    cAgencyTowerSegmentMission::cAgencyTowerSegmentMission() {}

    const Fun_Runtime::cClass &cAgencyTowerSegmentMission::RetClass() const
    {
        return *ms_pcAgencyTowerSegmentMissionClass;
    }

    const char *cAgencyTowerSegmentMission::RetClassName() const
    {
        return "cAgencyTowerSegmentMission";
    }

    bool cAgencyTowerSegmentMission::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcAgencyTowerSegmentMissionClass->IsA(c);
    }

    RWS::CAttributeHandler *cAgencyTowerSegmentMission::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cAgencyTowerSegmentMission();
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cAgencyTowerSegmentMissionRegistrar(
        "cAgencyTowerSegmentMission", cAgencyTowerSegmentMission::MakeNew, 0x710, false);
}

#include "cd2/memory.h"

namespace AI
{
    Fun_Runtime::cClass &cAgencyTowerSegmentMission::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAgencyTowerSegmentMissionClass = new Fun_Runtime::cClass(0x2104E, "cAgencyTowerSegmentMission", 0x710);
        return *cAgencyTowerSegmentMissionClass;
    }
}

#include "fun_runtime/inheritance_registrar.h"
#include "AI/cMission.h"

// CD2 0x82F88028: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar cAgencyTowerSegmentMissioncMissionInheritRegistrar(
        AI::cAgencyTowerSegmentMission::StaticCreateClass(), AI::cMission::StaticCreateClass());
}
