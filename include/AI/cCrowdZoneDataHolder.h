#ifndef AI_cCrowdZoneDataHolder_H
#define AI_cCrowdZoneDataHolder_H

#include "rws/attributes.h"

namespace AI
{
    class cCrowdZoneDataHolder : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
