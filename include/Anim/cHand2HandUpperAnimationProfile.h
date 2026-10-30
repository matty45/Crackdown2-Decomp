#ifndef Anim_cHand2HandUpperAnimationProfile_H
#define Anim_cHand2HandUpperAnimationProfile_H

#include "rws/attributes.h"

namespace Anim
{
    class cHand2HandUpperAnimationProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
