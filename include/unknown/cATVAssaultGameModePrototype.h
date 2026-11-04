#ifndef unknown_cATVAssaultGameModePrototype_H
#define unknown_cATVAssaultGameModePrototype_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace unknown
{
    class cATVAssaultGameModePrototype : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x8287B358 (MakeNew calls it).
        cATVAssaultGameModePrototype();

    private:
        unsigned char m_unmodelled18[0x260 - 0x18];

        CD2_LAYOUT_CHECKS(cATVAssaultGameModePrototype, CD2_SIZE(cATVAssaultGameModePrototype, 0x260))

    };
}

#endif
