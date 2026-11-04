#ifndef AI_CellGuard_H
#define AI_CellGuard_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace AI
{
    class CellGuard : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x824C5E78 (MakeNew calls it with the packet).
        CellGuard(const RWS::CAttributePacket &packet);

    private:
        unsigned char m_unmodelled18[0x100 - 0x18];

        CD2_LAYOUT_CHECKS(CellGuard, CD2_SIZE(CellGuard, 0x100))

    };
}

#endif
