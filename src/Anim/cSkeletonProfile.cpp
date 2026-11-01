#include "Anim/cSkeletonProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cSkeletonProfile::RetClassName() const
    {
        return "cSkeletonProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cSkeletonProfileRegistrar(
        "cSkeletonProfile", cSkeletonProfile::MakeNew, 0x190, false);
}

#include "cd2/memory.h"

namespace Anim
{
    Fun_Runtime::cClass &cSkeletonProfile::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cSkeletonProfileClass = new Fun_Runtime::cClass(0x5EF, "cSkeletonProfile", 0x190);
        return *cSkeletonProfileClass;
    }
}

namespace Anim
{
    const Fun_Runtime::cClass *cSkeletonProfile::ms_pcSkeletonProfileClass = &cSkeletonProfile::StaticCreateClass();

    const Fun_Runtime::cClass &cSkeletonProfile::RetClass() const
    {
        return *ms_pcSkeletonProfileClass;
    }
}

namespace Anim
{
    bool cSkeletonProfile::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcSkeletonProfileClass->IsA(c);
    }
}
