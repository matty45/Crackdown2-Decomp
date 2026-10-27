#include "AI/TrainingAmbient.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *TrainingAmbient::ms_pTrainingAmbientClass = 0;

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
    "TrainingAmbient", AI::TrainingAmbient::MakeNew, 0x7C, false);
