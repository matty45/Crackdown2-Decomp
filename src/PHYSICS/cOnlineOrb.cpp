#include "PHYSICS/cOnlineOrb.h"
#include "rws/classfactory.h"

namespace PHYSICS
{
    const char *cOnlineOrb::RetClassName() const
    {
        return "cOnlineOrb";
    }
}

namespace PHYSICS
{
    static RWS::CClassFactory::CRegistrar cOnlineOrbRegistrar(
        "cOnlineOrb", cOnlineOrb::MakeNew, 0x170, false);
}

#include "cd2/memory.h"

namespace PHYSICS
{
    Fun_Runtime::cClass &cOnlineOrb::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cOnlineOrbClass = new Fun_Runtime::cClass(0x116, "cOnlineOrb", 0x170);
        return *cOnlineOrbClass;
    }
}

namespace PHYSICS
{
    const Fun_Runtime::cClass *cOnlineOrb::ms_pcOnlineOrbClass = &cOnlineOrb::StaticCreateClass();

    const Fun_Runtime::cClass &cOnlineOrb::RetClass() const
    {
        return *ms_pcOnlineOrbClass;
    }
}
