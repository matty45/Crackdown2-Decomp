#include "rws/classfactory.h"
#include "GameManagement/cArenaCameraContainer.h"

namespace GameManagement
{
    const char *cArenaCameraContainer::RetClassName() const
    {
        return "cArenaCameraContainer";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cArenaCameraContainerRegistrar(
        "cArenaCameraContainer", cArenaCameraContainer::MakeNew, 0x28, false);
}
