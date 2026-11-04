#ifndef VFX_cDepthOfField_H
#define VFX_cDepthOfField_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace VFX
{
    class cDepthOfField : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x827958B0 (MakeNew calls it).
        cDepthOfField();

    private:
        unsigned char m_unmodelled18[0x8C - 0x18];

        CD2_LAYOUT_CHECKS(cDepthOfField, CD2_SIZE(cDepthOfField, 0x8C))

    };
}

#endif
