#include "GameManagement/cCHordeArena.h"
#include "rws/classfactory.h"

namespace GameManagement
{
    const char *cCHordeArena::RetClassName() const
    {
        return "cCHordeArena";
    }

    RWS::CAttributeHandler *cCHordeArena::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cCHordeArena();
    }
}

static RWS::CClassFactory::CRegistrar cCHordeArenaRegistrar(
    "cCHordeArena", GameManagement::cCHordeArena::MakeNew, 0x110, false);
