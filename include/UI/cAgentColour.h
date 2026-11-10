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

        // CD2: cAgentColour's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x82899C68
    private:
        CD2_LAYOUT_CHECKS(cAgentColour,
            CD2_SIZE(cAgentColour, 0x28))
    };
}

#endif
