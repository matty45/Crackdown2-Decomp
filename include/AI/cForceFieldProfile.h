#ifndef AI_cForceFieldProfile_H
#define AI_cForceFieldProfile_H

#include "rws/attributes.h"

namespace AI
{
    class cForceFieldProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
