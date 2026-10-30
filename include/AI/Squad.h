#ifndef AI_Squad_H
#define AI_Squad_H

#include "rws/attributes.h"

namespace AI
{
    class Squad : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
