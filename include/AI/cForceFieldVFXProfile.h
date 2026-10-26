#ifndef AI_cForceFieldVFXProfile_H
#define AI_cForceFieldVFXProfile_H

#include "rws/attributes.h"

namespace AI
{
    class cForceFieldVFXProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
