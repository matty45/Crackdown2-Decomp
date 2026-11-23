#ifndef unknown_cRenegadesGameModePrototype_H
#define unknown_cRenegadesGameModePrototype_H

#include "cd2/layout.h"
#include "rws/attributes.h"
#include "GameManagement/cPvPGameModePrototype.h"

namespace unknown
{
    // STAND-IN: constructor 0x828753B8 calls cPvPGameModePrototype's
    // constructor (0x8283E2F8); own fields remain unrecovered.
    class cRenegadesGameModePrototype : public GameManagement::cPvPGameModePrototype
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual int RetStringID() const;
    public:
        // Out of line: CD2 0x828753B8 (MakeNew calls it).
        cRenegadesGameModePrototype();

    private:
        unsigned char m_unmodelled148[0x1E8 - 0x148];

        CD2_LAYOUT_CHECKS(cRenegadesGameModePrototype, CD2_SIZE(cRenegadesGameModePrototype, 0x1E8))

    };
}

#endif
