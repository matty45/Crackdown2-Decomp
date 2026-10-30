#ifndef Anim_cSwimLaunchAnimationProfile_H
#define Anim_cSwimLaunchAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cSwimLaunchAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
