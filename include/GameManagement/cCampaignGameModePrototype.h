#ifndef GameManagement_cCampaignGameModePrototype_H
#define GameManagement_cCampaignGameModePrototype_H

#include "cd2/layout.h"
#include "rws/attributes.h"
#include "GameManagement/cGameModePrototype.h"

namespace GameManagement
{
    // CD2 constructor 0x82857550 calls cGameModePrototype (0x8283B2B8).
    class cCampaignGameModePrototype : public cGameModePrototype
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual int RetStringID() const; // primary slot 27: 0x82857650
    public:
        // Out of line: CD2 0x82857550 (MakeNew calls it).
        cCampaignGameModePrototype();

    private:
        unsigned char m_unmodelledF8[0x120 - 0xF8];

        CD2_LAYOUT_CHECKS(cCampaignGameModePrototype, CD2_SIZE(cCampaignGameModePrototype, 0x120))

    };
}

#endif
