#ifndef Anim_cTransformationAnimationProfile_H
#define Anim_cTransformationAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cTransformationAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
