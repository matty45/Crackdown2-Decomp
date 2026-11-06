// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "RPG/cRPGGlobalsInterface.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace RPG
{
    const char *cRPGGlobalsInterface::RetClassName() const
    {
        return "cRPGGlobalsInterface";
    }

    RWS::CAttributeHandler *cRPGGlobalsInterface::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        cRPGGlobalsInterface *p = new cRPGGlobalsInterface();
        return p;
    }

    static RWS::CClassFactory::CRegistrar cRPGGlobalsInterfaceRegistrar(
        "cRPGGlobalsInterface", cRPGGlobalsInterface::MakeNew, 0x18, false);
}
