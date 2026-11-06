// STAND-IN: CD2 constructor 0x8287B358 calls cPvPGameModePrototype at 0x8283E2F8.
#ifndef unknown_cATVAssaultGameModePrototype_H
#define unknown_cATVAssaultGameModePrototype_H

#include "cd2/layout.h"
#include "GameManagement/cPvPGameModePrototype.h"

namespace unknown
{
    class cATVAssaultGameModePrototype : public GameManagement::cPvPGameModePrototype
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void Destruct();
        virtual int RetStringID() const;
    public:
        // Out of line: CD2 0x8287B358 (MakeNew calls it).
        cATVAssaultGameModePrototype();

    private:
        unsigned char m_unmodelled148[0x260 - 0x148];

        CD2_LAYOUT_CHECKS(cATVAssaultGameModePrototype, CD2_SIZE(cATVAssaultGameModePrototype, 0x260))

    };
}

#endif
