#ifndef unknown_cTeamHunterGathererGameModePrototype_H
#define unknown_cTeamHunterGathererGameModePrototype_H

#include "rws/attributes.h"

namespace unknown
{
    class cTeamHunterGathererGameModePrototype : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
