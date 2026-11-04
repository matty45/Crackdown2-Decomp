#ifndef VFX_cDeityRay_H
#define VFX_cDeityRay_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace VFX
{
    class cDeityRay : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x82792528 (MakeNew calls it).
        cDeityRay();

    private:
        unsigned char m_unmodelled18[0x6B0 - 0x18];

        CD2_LAYOUT_CHECKS(cDeityRay, CD2_SIZE(cDeityRay, 0x6B0))

    };
}

#endif
