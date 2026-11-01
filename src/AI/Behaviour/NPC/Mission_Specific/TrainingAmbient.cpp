#include "AI/TrainingAmbient.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *TrainingAmbient::ms_pTrainingAmbientClass = &TrainingAmbient::StaticCreateClass();

    TrainingAmbient::TrainingAmbient() {}

    const Fun_Runtime::cClass &TrainingAmbient::RetClass() const
    {
        return *ms_pTrainingAmbientClass;
    }

    const char *TrainingAmbient::RetClassName() const
    {
        return "TrainingAmbient";
    }

    bool TrainingAmbient::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pTrainingAmbientClass->IsA(c);
    }

    RWS::CAttributeHandler *TrainingAmbient::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new TrainingAmbient();
    }
}

static RWS::CClassFactory::CRegistrar TrainingAmbientRegistrar(
    "TrainingAmbient", AI::TrainingAmbient::MakeNew, 0xD0, false);

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &TrainingAmbient::StaticCreateClass()
    {
        static Fun_Runtime::cClass *TrainingAmbientClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "TrainingAmbient", 0xD0);
        return *TrainingAmbientClass;
    }
}
