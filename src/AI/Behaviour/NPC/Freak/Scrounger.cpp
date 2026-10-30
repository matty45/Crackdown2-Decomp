#include "AI/Scrounger.h"
#include "rws/classfactory.h"

namespace AI
{
    const char *Scrounger::RetClassName() const
    {
        return "Scrounger";
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar ScroungerRegistrar(
        "Scrounger", Scrounger::MakeNew, 0x130, false);
}
