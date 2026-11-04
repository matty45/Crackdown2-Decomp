#ifndef GameManagement_cTrainingRespawnPoint_H
#define GameManagement_cTrainingRespawnPoint_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace GameManagement
{
    class cTrainingRespawnPoint : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x82858728 (MakeNew calls it with the packet).
        cTrainingRespawnPoint(const RWS::CAttributePacket &packet);

    private:
        unsigned char m_unmodelled18[0x80 - 0x18];

        CD2_LAYOUT_CHECKS(cTrainingRespawnPoint, CD2_SIZE(cTrainingRespawnPoint, 0x80))

    };
}

#endif
