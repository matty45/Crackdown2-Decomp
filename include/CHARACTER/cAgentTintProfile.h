#ifndef CHARACTER_cAgentTintProfile_H
#define CHARACTER_cAgentTintProfile_H

#include "rws/attributes.h"
#include "cd2/layout.h"

namespace CHARACTER
{
    class cAgentTintProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif
