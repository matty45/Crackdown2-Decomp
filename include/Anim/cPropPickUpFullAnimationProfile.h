#ifndef Anim_cPropPickUpFullAnimationProfile_H
#define Anim_cPropPickUpFullAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cPropPickUpFullAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
