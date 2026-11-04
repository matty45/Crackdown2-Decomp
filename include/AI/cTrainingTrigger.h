#ifndef AI_cTrainingTrigger_H
#define AI_cTrainingTrigger_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace AI
{
    class cTrainingTrigger : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x824855F0 (MakeNew calls it with the packet).
        cTrainingTrigger(const RWS::CAttributePacket &packet);

    private:
        unsigned char m_unmodelled18[0x110 - 0x18];

        CD2_LAYOUT_CHECKS(cTrainingTrigger, CD2_SIZE(cTrainingTrigger, 0x110))

    };
}

#endif
