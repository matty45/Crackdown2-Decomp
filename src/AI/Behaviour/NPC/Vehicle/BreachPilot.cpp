#include "AI/BreachPilot.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *BreachPilot::ms_pBreachPilotClass = &BreachPilot::StaticCreateClass();

    BreachPilot::BreachPilot() {}

    const Fun_Runtime::cClass &BreachPilot::RetClass() const
    {
        return *ms_pBreachPilotClass;
    }

    const char *BreachPilot::RetClassName() const
    {
        return "BreachPilot";
    }

    bool BreachPilot::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pBreachPilotClass->IsA(c);
    }

    RWS::CAttributeHandler *BreachPilot::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new BreachPilot();
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar BreachPilotRegistrar(
        "BreachPilot", BreachPilot::MakeNew, 0x160, false);
}

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &BreachPilot::StaticCreateClass()
    {
        static Fun_Runtime::cClass *BreachPilotClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "BreachPilot", 0x160);
        return *BreachPilotClass;
    }
}
