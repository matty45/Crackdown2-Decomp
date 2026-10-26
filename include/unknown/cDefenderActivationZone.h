#ifndef unknown_cDefenderActivationZone_H
#define unknown_cDefenderActivationZone_H

#include "rws/attributes.h"

namespace unknown
{
    class cDefenderActivationZone : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
