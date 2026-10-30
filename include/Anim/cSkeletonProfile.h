#ifndef Anim_cSkeletonProfile_H
#define Anim_cSkeletonProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cSkeletonProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
