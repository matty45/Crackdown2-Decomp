#include "AI/cTopOfTheWorldTrigger.h"
#include "rws/classfactory.h"

namespace AI
{
    const char *cTopOfTheWorldTrigger::RetClassName() const
    {
        return "cTopOfTheWorldTrigger";
    }

    static RWS::CClassFactory::CRegistrar cTopOfTheWorldTriggerRegistrar(
        "cTopOfTheWorldTrigger", cTopOfTheWorldTrigger::MakeNew, 0xE0, false);
}
