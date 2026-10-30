#ifndef unknown_cDefenderActivationZone_H
#define unknown_cDefenderActivationZone_H

#include "rws/attributes.h"

namespace unknown
{
    class cDefenderActivationZone : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
