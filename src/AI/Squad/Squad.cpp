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

#include "cd2/memory.h"

namespace AI
{
    Fun_Runtime::cClass &Squad::StaticCreateClass()
    {
        static Fun_Runtime::cClass *SquadClass = new Fun_Runtime::cClass(0x6A597, "Squad", 0x390);
        return *SquadClass;
    }
}

namespace AI
{
    const Fun_Runtime::cClass *Squad::ms_pSquadClass = &Squad::StaticCreateClass();

    const Fun_Runtime::cClass &Squad::RetClass() const
    {
        return *ms_pSquadClass;
    }
}

namespace AI
{
    bool Squad::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pSquadClass->IsA(c);
    }
}
