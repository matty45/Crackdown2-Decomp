#ifndef AI_cTopOfTheWorldTrigger_H
#define AI_cTopOfTheWorldTrigger_H

#include "rws/attributes.h"

namespace AI
{
    class cTopOfTheWorldTrigger : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
