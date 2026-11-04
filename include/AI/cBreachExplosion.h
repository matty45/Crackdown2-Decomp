#ifndef AI_cBreachExplosion_H
#define AI_cBreachExplosion_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace AI
{
    class cBreachExplosion : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x822C11B0 (MakeNew calls it).
        cBreachExplosion();

    private:
        unsigned char m_unmodelled18[0x90 - 0x18];

        CD2_LAYOUT_CHECKS(cBreachExplosion, CD2_SIZE(cBreachExplosion, 0x90))

    };
}

#endif
