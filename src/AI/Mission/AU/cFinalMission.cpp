#include "fun_runtime/inheritance_registrar.h"
#include "AI/cFinalMission.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace AI
{
    const Fun_Runtime::cClass *cFinalMission::ms_pcFinalMissionClass = &cFinalMission::StaticCreateClass();

    cFinalMission::cFinalMission() {}

    const Fun_Runtime::cClass &cFinalMission::RetClass() const
    {
        return *ms_pcFinalMissionClass;
    }

    const char *cFinalMission::RetClassName() const
    {
        return "cFinalMission";
    }

    bool cFinalMission::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcFinalMissionClass->IsA(c);
    }

    RWS::CAttributeHandler *cFinalMission::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cFinalMission();
    }

    static RWS::CClassFactory::CRegistrar cFinalMissionRegistrar(
        "cFinalMission", cFinalMission::MakeNew, 0xC50, false);

    Fun_Runtime::cClass &cFinalMission::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cFinalMissionClass = new Fun_Runtime::cClass(0x2A1FD, "cFinalMission", 0xC50);
        return *cFinalMissionClass;
    }

    // CD2 0x82F89330: runtime mission inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cFinalMissioncMissionInheritRegistrar(
        AI::cFinalMission::StaticCreateClass(), AI::cMission::StaticCreateClass());
}
