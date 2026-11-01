#include "Prop/cPintleFaceplate.h"
#include "rws/classfactory.h"

namespace Prop
{
    const char *cPintleFaceplate::RetClassName() const
    {
        return "cPintleFaceplate";
    }
}

namespace Prop
{
    static RWS::CClassFactory::CRegistrar cPintleFaceplateRegistrar(
        "cPintleFaceplate", cPintleFaceplate::MakeNew, 0xE40, false);
}

#include "cd2/memory.h"

namespace Prop
{
    Fun_Runtime::cClass &cPintleFaceplate::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cPintleFaceplateClass = new Fun_Runtime::cClass(0xD439, "cPintleFaceplate", 0xE40);
        return *cPintleFaceplateClass;
    }
}

namespace Prop
{
    const Fun_Runtime::cClass *cPintleFaceplate::ms_pcPintleFaceplateClass = &cPintleFaceplate::StaticCreateClass();

    const Fun_Runtime::cClass &cPintleFaceplate::RetClass() const
    {
        return *ms_pcPintleFaceplateClass;
    }
}

namespace Prop
{
    bool cPintleFaceplate::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcPintleFaceplateClass->IsA(c);
    }
}
