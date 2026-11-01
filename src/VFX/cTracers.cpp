#include "VFX/cTracers.h"

namespace VFX
{
    const char *cTracers::RetClassName() const
    {
        return "cTracers";
    }
}

#include "cd2/memory.h"

namespace VFX
{
    Fun_Runtime::cClass &cTracers::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cTracersClass = new Fun_Runtime::cClass(0x1F97D, "cTracers", 0x138);
        return *cTracersClass;
    }
}

namespace VFX
{
    const Fun_Runtime::cClass *cTracers::ms_pcTracersClass = &cTracers::StaticCreateClass();
}
