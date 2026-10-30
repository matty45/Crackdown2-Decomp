#ifndef CHARACTER_cGlobalControlsProfile_H
#define CHARACTER_cGlobalControlsProfile_H

#include "rws/attributes.h"

namespace CHARACTER
{
    class cGlobalControlsProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
