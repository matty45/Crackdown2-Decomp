#ifndef UI_cAgentColour_H
#define UI_cAgentColour_H

#include "rws/attributes.h"
#include "cd2/layout.h"

namespace UI
{
    class cAgentColour : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);

    private:
        unsigned char m_pad[0x28 - 0x18];

        CD2_LAYOUT_CHECKS(cAgentColour,
            CD2_SIZE(cAgentColour, 0x28))
    };
}

#endif
