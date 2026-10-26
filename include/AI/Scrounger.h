#ifndef AI_Scrounger_H
#define AI_Scrounger_H

#include "rws/attributes.h"

namespace AI
{
    class Scrounger : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
