#include "rws/attributes.h"
// GameManagement::cTeamDeathMatchGameModePrototype (Crackdown 2): STAND-IN with only what its matched functions need; its bases are not modelled yet.
// Its class-factory registrar (0x83018738) registers "cTeamDeathMatchGameModePrototype" with MakeNew (0x82851968) and size 0x190.
// Reconstruction update: MakeNew calls cPvPGameModePrototype's constructor
// 0x8283E2F8 and installs table 0x8215C298. Own storage remains unrecovered.
#ifndef GAMEMANAGEMENT_CTEAMDEATHMATCHGAMEMODEPROTOTYPE_H
#define GAMEMANAGEMENT_CTEAMDEATHMATCHGAMEMODEPROTOTYPE_H
#include "GameManagement/cPvPGameModePrototype.h"

namespace GameManagement
{
    class cTeamDeathMatchGameModePrototype : public cPvPGameModePrototype
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const; // primary slot 42: 0x828519E0
        virtual int RetStringID() const; // primary slot 27: 0x82851A08
    };
}

#endif // GAMEMANAGEMENT_CTEAMDEATHMATCHGAMEMODEPROTOTYPE_H
