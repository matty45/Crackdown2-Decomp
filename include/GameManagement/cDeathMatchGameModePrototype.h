#ifndef GameManagement_cDeathMatchGameModePrototype_H
#define GameManagement_cDeathMatchGameModePrototype_H

#include "rws/attributes.h"
#include "GameManagement/cPvPGameModePrototype.h"

namespace GameManagement
{
    // Method-only stand-in: CD2 MakeNew 0x8284FA40 calls the shared PvP
    // constructor 0x8283E2F8 before installing table 0x8215BFB0.
    class cDeathMatchGameModePrototype : public cPvPGameModePrototype
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual int RetStringID() const; // primary slot 27: 0x8284FAC8
    };
}

#endif
