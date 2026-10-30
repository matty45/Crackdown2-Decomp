#include "AI/Squad.h"
#include "rws/classfactory.h"

namespace AI
{
    const char *Squad::RetClassName() const
    {
        return "Squad";
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar SquadRegistrar(
        "Squad", Squad::MakeNew, 0x390, false);
}
