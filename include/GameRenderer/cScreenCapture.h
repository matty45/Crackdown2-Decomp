#ifndef GameRenderer_cScreenCapture_H
#define GameRenderer_cScreenCapture_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace GameRenderer
{
    class cScreenCapture : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x826661F0 (MakeNew calls it).
        cScreenCapture();

    private:
        unsigned char m_unmodelled18[0x1F0 - 0x18];

        CD2_LAYOUT_CHECKS(cScreenCapture, CD2_SIZE(cScreenCapture, 0x1F0))

    };
}

#endif
