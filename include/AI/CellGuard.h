#ifndef AI_CellGuard_H
#define AI_CellGuard_H

#include "rws/attributes.h"

namespace AI
{
    class CellGuard : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
