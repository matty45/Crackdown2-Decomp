#ifndef unknown_cRenegadesGameModePrototype_H
#define unknown_cRenegadesGameModePrototype_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace unknown
{
    class cRenegadesGameModePrototype : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x828753B8 (MakeNew calls it).
        cRenegadesGameModePrototype();

    private:
        unsigned char m_unmodelled18[0x1E8 - 0x18];

        CD2_LAYOUT_CHECKS(cRenegadesGameModePrototype, CD2_SIZE(cRenegadesGameModePrototype, 0x1E8))

    };
}

#endif
