#ifndef GameManagement_cCampaignPlayerSpawnPoint_H
#define GameManagement_cCampaignPlayerSpawnPoint_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace GameManagement
{
    class cCampaignPlayerSpawnPoint : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x8284A6E8 (MakeNew calls it).
        cCampaignPlayerSpawnPoint();

    private:
        unsigned char m_unmodelled18[0x80 - 0x18];

        CD2_LAYOUT_CHECKS(cCampaignPlayerSpawnPoint, CD2_SIZE(cCampaignPlayerSpawnPoint, 0x80))

    };
}

#endif
