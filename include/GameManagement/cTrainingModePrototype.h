#ifndef GameManagement_cTrainingModePrototype_H
#define GameManagement_cTrainingModePrototype_H

#include "rws/attributes.h"
#include "GameManagement/cGameModePrototype.h"

namespace GameManagement
{
    // Method-only stand-in: CD2 MakeNew 0x82858328 calls cGameModePrototype
    // (0x8283B2B8). The GUID handler at +0xF8 is not modelled here yet.
    class cTrainingModePrototype : public cGameModePrototype
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual int RetStringID() const; // primary slot 27: 0x82858458
    };
}

#endif
