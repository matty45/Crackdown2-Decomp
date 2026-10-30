#ifndef Anim_cTurretsAnimationProfile_H
#define Anim_cTurretsAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cTurretsAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
