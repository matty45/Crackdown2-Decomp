#ifndef GameRenderer_cCD2Lighting_H
#define GameRenderer_cCD2Lighting_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace GameRenderer
{
    class cCD2Lighting : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x82388F10 (MakeNew calls it).
        cCD2Lighting();

    private:
        unsigned char m_unmodelled18[0x2680 - 0x18];

        CD2_LAYOUT_CHECKS(cCD2Lighting, CD2_SIZE(cCD2Lighting, 0x2680))

    };
}

#endif
