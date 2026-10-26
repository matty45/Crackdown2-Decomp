#ifndef unknown_cLaunchPadLocation_H
#define unknown_cLaunchPadLocation_H

#include "rws/attributes.h"

namespace unknown
{
    class cLaunchPadLocation : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
