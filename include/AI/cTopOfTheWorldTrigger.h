#ifndef AI_cTopOfTheWorldTrigger_H
#define AI_cTopOfTheWorldTrigger_H

#include "rws/attributes.h"

namespace AI
{
    class cTopOfTheWorldTrigger : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
