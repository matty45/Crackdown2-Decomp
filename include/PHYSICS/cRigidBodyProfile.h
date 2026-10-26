#ifndef PHYSICS_cRigidBodyProfile_H
#define PHYSICS_cRigidBodyProfile_H

#include "rws/attributes.h"

namespace PHYSICS
{
    class cRigidBodyProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
