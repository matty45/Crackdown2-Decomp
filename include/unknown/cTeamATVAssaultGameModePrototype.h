#ifndef unknown_cTeamATVAssaultGameModePrototype_H
#define unknown_cTeamATVAssaultGameModePrototype_H

#include "unknown/cATVAssaultGameModePrototype.h"

namespace unknown
{
    class cTeamATVAssaultGameModePrototype : public cATVAssaultGameModePrototype
    {
    public:
        // CD2 factory 0x8287E080 inlines this over cATVAssaultGameModePrototype.
        __forceinline cTeamATVAssaultGameModePrototype() {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual int RetStringID() const;
    };
}

#endif
