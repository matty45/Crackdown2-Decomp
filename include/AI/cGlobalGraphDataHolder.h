#ifndef AI_cGlobalGraphDataHolder_H
#define AI_cGlobalGraphDataHolder_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace AI
{
    class cGlobalGraphDataHolder : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x821D5290 (MakeNew calls it with the packet).
        cGlobalGraphDataHolder(const RWS::CAttributePacket &packet);

        CD2_LAYOUT_CHECKS(cGlobalGraphDataHolder, CD2_SIZE(cGlobalGraphDataHolder, 0x18))

    };
}

#endif
