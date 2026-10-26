#ifndef CHARACTER_cGlobalControlsProfile_H
#define CHARACTER_cGlobalControlsProfile_H

#include "rws/attributes.h"

namespace CHARACTER
{
    class cGlobalControlsProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
