// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
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
