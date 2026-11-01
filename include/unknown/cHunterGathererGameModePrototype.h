#ifndef unknown_cHunterGathererGameModePrototype_H
#define unknown_cHunterGathererGameModePrototype_H

#include "rws/attributes.h"

namespace unknown
{
    class cHunterGathererGameModePrototype : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
