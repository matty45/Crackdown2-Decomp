#include "rws/classfactory.h"
#include "GameManagement/cArenaCameraContainer.h"
#include "cd2/memory.h"

namespace GameManagement
{
    RWS::CAttributeHandler *cArenaCameraContainer::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cArenaCameraContainer(packet);
    }

    const char *cArenaCameraContainer::RetClassName() const
    {
        return "cArenaCameraContainer";
    }

    cArenaCameraContainer::~cArenaCameraContainer()
    {
    }

    static RWS::CClassFactory::CRegistrar cArenaCameraContainerRegistrar(
        "cArenaCameraContainer", cArenaCameraContainer::MakeNew, 0x28, false);
}
