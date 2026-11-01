#ifndef unknown_cTeamATVAssaultGameModePrototype_H
#define unknown_cTeamATVAssaultGameModePrototype_H

#include "rws/attributes.h"

namespace unknown
{
    class cTeamATVAssaultGameModePrototype : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
