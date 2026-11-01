#include "AI/cAUMission.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cAUMission::ms_pcAUMissionClass = &cAUMission::StaticCreateClass();

    cAUMission::cAUMission() {}

    const Fun_Runtime::cClass &cAUMission::RetClass() const
    {
        return *ms_pcAUMissionClass;
    }

    const char *cAUMission::RetClassName() const
    {
        return "cAUMission";
    }

    bool cAUMission::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcAUMissionClass->IsA(c);
    }

    RWS::CAttributeHandler *cAUMission::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cAUMission();
    }
}

static RWS::CClassFactory::CRegistrar cAUMissionRegistrar(
    "cAUMission", AI::cAUMission::MakeNew, 0x5F0, false);

#include "cd2/memory.h"

namespace AI
{
    Fun_Runtime::cClass &cAUMission::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAUMissionClass = new Fun_Runtime::cClass(0x205C2, "cAUMission", 0x5F0);
        return *cAUMissionClass;
    }
}
