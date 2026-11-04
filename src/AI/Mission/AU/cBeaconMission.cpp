#include "AI/cBeaconMission.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cBeaconMission::ms_pcBeaconMissionClass = &cBeaconMission::StaticCreateClass();

    cBeaconMission::cBeaconMission() {}

    const Fun_Runtime::cClass &cBeaconMission::RetClass() const
    {
        return *ms_pcBeaconMissionClass;
    }

    const char *cBeaconMission::RetClassName() const
    {
        return "cBeaconMission";
    }

    bool cBeaconMission::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcBeaconMissionClass->IsA(c);
    }

    RWS::CAttributeHandler *cBeaconMission::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cBeaconMission();
    }
}

static RWS::CClassFactory::CRegistrar cBeaconMissionRegistrar(
    "cBeaconMission", AI::cBeaconMission::MakeNew, 0x2300, false);

#include "cd2/memory.h"

namespace AI
{
    Fun_Runtime::cClass &cBeaconMission::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cBeaconMissionClass = new Fun_Runtime::cClass(0x205C3, "cBeaconMission", 0x2300);
        return *cBeaconMissionClass;
    }
}

#include "fun_runtime/inheritance_registrar.h"
#include "AI/cMission.h"

// CD2 0x82F88C20: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar cBeaconMissioncMissionInheritRegistrar(
        AI::cBeaconMission::StaticCreateClass(), AI::cMission::StaticCreateClass());
}
