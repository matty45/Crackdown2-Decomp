#ifndef GameManagement_cMiniGameTier_H
#define GameManagement_cMiniGameTier_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cMiniGameTier : public RWS::CAttributeHandler
    {
        // STAND-IN: unmodelled members. CD2 MakeNew and registrar allocate/register
        // 0x64 bytes, agreeing with RuffKing's class size and CAttributeHandler base.
        unsigned char m_unmodelled18[0x64 - 0x18];
    public:
        cMiniGameTier(); // CD2 0x82884718; the factory passes only this
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        CD2_LAYOUT_CHECKS(cMiniGameTier, CD2_SIZE(cMiniGameTier, 0x64))
    };
}

#endif
