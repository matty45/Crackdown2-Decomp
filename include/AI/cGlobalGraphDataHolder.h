#ifndef AI_cGlobalGraphDataHolder_H
#define AI_cGlobalGraphDataHolder_H

#include "rws/attributes.h"

namespace AI
{
    class cGlobalGraphDataHolder : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
