#include "AI/cTrainingHeliPilot.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cTrainingHeliPilot::ms_pcTrainingHeliPilotClass = &cTrainingHeliPilot::StaticCreateClass();

    cTrainingHeliPilot::cTrainingHeliPilot() {}

    const Fun_Runtime::cClass &cTrainingHeliPilot::RetClass() const
    {
        return *ms_pcTrainingHeliPilotClass;
    }

    const char *cTrainingHeliPilot::RetClassName() const
    {
        return "cTrainingHeliPilot";
    }

    bool cTrainingHeliPilot::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcTrainingHeliPilotClass->IsA(c);
    }

    RWS::CAttributeHandler *cTrainingHeliPilot::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cTrainingHeliPilot();
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cTrainingHeliPilotRegistrar(
        "cTrainingHeliPilot", cTrainingHeliPilot::MakeNew, 0x150, false);
}

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &cTrainingHeliPilot::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cTrainingHeliPilotClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "cTrainingHeliPilot", 0x150);
        return *cTrainingHeliPilotClass;
    }
}
