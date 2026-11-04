#include "rws/attributes.h"
// GameManagement::cTeamDeathMatchGameModePrototype (Crackdown 2): STAND-IN with only what its matched functions need; its bases are not modelled yet.
// Its class-factory registrar (0x83018738) registers "cTeamDeathMatchGameModePrototype" with MakeNew (0x82851968) and size 0x190.
#ifndef GAMEMANAGEMENT_CTEAMDEATHMATCHGAMEMODEPROTOTYPE_H
#define GAMEMANAGEMENT_CTEAMDEATHMATCHGAMEMODEPROTOTYPE_H

namespace GameManagement
{
    class cTeamDeathMatchGameModePrototype
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // GAMEMANAGEMENT_CTEAMDEATHMATCHGAMEMODEPROTOTYPE_H
