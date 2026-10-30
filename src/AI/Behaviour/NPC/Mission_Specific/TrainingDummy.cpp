#include "AI/TrainingDummy.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *TrainingDummy::ms_pTrainingDummyClass = 0;

    TrainingDummy::TrainingDummy() {}

    const Fun_Runtime::cClass &TrainingDummy::RetClass() const
    {
        return *ms_pTrainingDummyClass;
    }

    const char *TrainingDummy::RetClassName() const
    {
        return "TrainingDummy";
    }

    bool TrainingDummy::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pTrainingDummyClass->IsA(c);
    }

    RWS::CAttributeHandler *TrainingDummy::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new TrainingDummy();
    }
}

static RWS::CClassFactory::CRegistrar TrainingDummyRegistrar(
    "TrainingDummy", AI::TrainingDummy::MakeNew, 0x7C, false);

namespace AI
{
    static RWS::CClassFactory::CRegistrar TrainingDummyRegistrar(
        "TrainingDummy", TrainingDummy::MakeNew, 0xD0, false);
}
