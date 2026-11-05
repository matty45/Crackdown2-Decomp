#include "AI/cTrainingTrigger.h"
#include "rws/classfactory.h"

namespace AI
{
    const char *cTrainingTrigger::RetClassName() const
    {
        return "cTrainingTrigger";
    }

    // CD2 0x82485720: only the member's and the bases' destruction.
    cTrainingTrigger::~cTrainingTrigger()
    {
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cTrainingTriggerRegistrar(
        "cTrainingTrigger", cTrainingTrigger::MakeNew, 0x110, false);
}

#include "cd2/memory.h"

// CD2 0x82485588: the class-factory constructor; the constructor stays out of line.
namespace AI
{
    RWS::CAttributeHandler *cTrainingTrigger::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cTrainingTrigger(packet);
    }
}
