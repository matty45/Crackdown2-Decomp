#ifndef AI_Scrounger_H
#define AI_Scrounger_H

#include "rws/attributes.h"

namespace AI
{
    class Scrounger : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
