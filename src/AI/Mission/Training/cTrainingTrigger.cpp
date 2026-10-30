#include "AI/cTrainingTrigger.h"
#include "rws/classfactory.h"

namespace AI
{
    const char *cTrainingTrigger::RetClassName() const
    {
        return "cTrainingTrigger";
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cTrainingTriggerRegistrar(
        "cTrainingTrigger", cTrainingTrigger::MakeNew, 0x110, false);
}
