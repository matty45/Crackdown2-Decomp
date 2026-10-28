#include "GameRenderer/CNonEntity.h"
#include "rws/classfactory.h"

namespace GameRenderer
{
    const char *CNonEntity::RetClassName() const
    {
        return "CNonEntity";
    }

    RWS::CAttributeHandler *CNonEntity::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        CNonEntity *p = new CNonEntity();
        return p;
    }

    static RWS::CClassFactory::CRegistrar CNonEntityRegistrar(
        "CNonEntity", CNonEntity::MakeNew, 0x1c, false);
}
