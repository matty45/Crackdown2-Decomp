#ifndef unknown_cHunterGathererGameModePrototype_H
#define unknown_cHunterGathererGameModePrototype_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace unknown
{
    class cHunterGathererGameModePrototype : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x8287E2B0 (MakeNew calls it).
        cHunterGathererGameModePrototype();

    private:
        unsigned char m_unmodelled18[0x198 - 0x18];

        CD2_LAYOUT_CHECKS(cHunterGathererGameModePrototype, CD2_SIZE(cHunterGathererGameModePrototype, 0x198))

    };
}

#endif
