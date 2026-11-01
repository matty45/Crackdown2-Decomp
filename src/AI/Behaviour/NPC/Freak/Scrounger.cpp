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

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &Scrounger::StaticCreateClass()
    {
        static Fun_Runtime::cClass *ScroungerClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "Scrounger", 0x130);
        return *ScroungerClass;
    }
}

namespace AI
{
    const Fun_Runtime::cClass *Scrounger::ms_pScroungerClass = &Scrounger::StaticCreateClass();

    const Fun_Runtime::cClass &Scrounger::RetClass() const
    {
        return *ms_pScroungerClass;
    }
}

namespace AI
{
    bool Scrounger::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pScroungerClass->IsA(c);
    }
}
