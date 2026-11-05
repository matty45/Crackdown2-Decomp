#include "rws/classfactory.h"
#include "GameManagement/cNetGameSpawnPoint.h"
#include "cd2/memory.h"

namespace GameManagement
{
    cNetGameSpawnPoint::cNetGameSpawnPoint() : m_nArenaIndex(-1)
    {
    }

    cNetGameSpawnPoint::~cNetGameSpawnPoint()
    {
    }

    void cNetGameSpawnPoint::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cGameModeSpawnPoint::HandleAttributes(packet);
        for (RWS::CAttributeCommandIterator it(packet, "cNetGameSpawnPoint"); !it.IsFinished(); ++it)
        {
            switch (it->GetCommandId())
            {
            case 0:
                m_sArenaName = it->GetAs_char_ptr();
                break;
            }
        }
    }

    const char *cNetGameSpawnPoint::RetClassName() const
    {
        return "cNetGameSpawnPoint";
    }

    static RWS::CClassFactory::CRegistrar cNetGameSpawnPointRegistrar(
        "cNetGameSpawnPoint", cNetGameSpawnPoint::MakeNew, 0x80, false);

    // CD2 0x8284D8B0: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cNetGameSpawnPoint::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cNetGameSpawnPoint;
    }
}
