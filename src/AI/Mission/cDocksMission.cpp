#include "fun_runtime/inheritance_registrar.h"
#include "AI/cDocksMission.h"
#include "rws/classfactory.h"

namespace AI
{
    const char *cDocksMission::RetClassName() const
    {
        return "cDocksMission";
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cDocksMissionRegistrar(
        "cDocksMission", cDocksMission::MakeNew, 0x450, false);
}

#include "cd2/memory.h"

namespace AI
{
    Fun_Runtime::cClass &cDocksMission::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cDocksMissionClass = new Fun_Runtime::cClass(0x9F4FE, "cDocksMission", 0x450);
        return *cDocksMissionClass;
    }
}

namespace AI
{
    const Fun_Runtime::cClass *cDocksMission::ms_pcDocksMissionClass = &cDocksMission::StaticCreateClass();

    const Fun_Runtime::cClass &cDocksMission::RetClass() const
    {
        return *ms_pcDocksMissionClass;
    }
}

namespace AI
{
    bool cDocksMission::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcDocksMissionClass->IsA(c);
    }
}

// CD2 0x82F8A480: runtime mission inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar cDocksMissioncMissionInheritRegistrar(
        AI::cDocksMission::StaticCreateClass(), AI::cMission::StaticCreateClass());
}
