#ifndef GameManagement_cCampaignGameModePrototype_H
#define GameManagement_cCampaignGameModePrototype_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace GameManagement
{
    class cCampaignGameModePrototype : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x82857550 (MakeNew calls it).
        cCampaignGameModePrototype();

    private:
        unsigned char m_unmodelled18[0x120 - 0x18];

        CD2_LAYOUT_CHECKS(cCampaignGameModePrototype, CD2_SIZE(cCampaignGameModePrototype, 0x120))

    };
}

#endif
