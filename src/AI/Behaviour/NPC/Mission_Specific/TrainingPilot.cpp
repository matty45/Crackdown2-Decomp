#include "AI/TrainingPilot.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *TrainingPilot::ms_pTrainingPilotClass = &TrainingPilot::StaticCreateClass();

    TrainingPilot::TrainingPilot() {}

    const Fun_Runtime::cClass &TrainingPilot::RetClass() const
    {
        return *ms_pTrainingPilotClass;
    }

    const char *TrainingPilot::RetClassName() const
    {
        return "TrainingPilot";
    }

    bool TrainingPilot::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pTrainingPilotClass->IsA(c);
    }

    RWS::CAttributeHandler *TrainingPilot::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new TrainingPilot();
    }
}

static RWS::CClassFactory::CRegistrar TrainingPilotRegistrar(
    "TrainingPilot", AI::TrainingPilot::MakeNew, 0xD0, false);

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &TrainingPilot::StaticCreateClass()
    {
        static Fun_Runtime::cClass *TrainingPilotClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "TrainingPilot", 0xD0);
        return *TrainingPilotClass;
    }
}
