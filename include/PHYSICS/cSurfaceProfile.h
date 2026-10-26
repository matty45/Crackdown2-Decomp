#ifndef PHYSICS_cSurfaceProfile_H
#define PHYSICS_cSurfaceProfile_H

#include "rws/attributes.h"

namespace PHYSICS
{
    class cSurfaceProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
