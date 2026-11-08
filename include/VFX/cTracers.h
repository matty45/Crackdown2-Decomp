#ifndef VFX_cTracers_H
#define VFX_cTracers_H

#include "cd2/layout.h"
#include "rws/attributes.h"
#include "fun_runtime/class.h"
#include "gom/non_game_base.h"

namespace VFX
{
    // Known wrong, left for a structural fix: RuffKing derives cTracers from cNonGameBase and GDb::cDebugPageHandler; CD2 registers
    // only cNonGameBase (0x83008808). If the second base is there, its vptr sits in the unmodelled bytes after 0x7C.
    class cTracers : public cNonGameBase
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcTracersClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x827B9A20 (MakeNew calls it).
        cTracers();

    private:
        unsigned char m_unmodelled7C[0x138 - 0x7C];

        CD2_LAYOUT_CHECKS(cTracers, CD2_SIZE(cTracers, 0x138))

    };
}

#endif
