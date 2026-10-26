#ifndef Anim_cSkeletonProfile_H
#define Anim_cSkeletonProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cSkeletonProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
