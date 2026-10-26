#ifndef AI_Squad_H
#define AI_Squad_H

#include "rws/attributes.h"

namespace AI
{
    class Squad : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
