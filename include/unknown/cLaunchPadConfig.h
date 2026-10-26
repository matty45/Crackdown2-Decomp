#ifndef unknown_cLaunchPadConfig_H
#define unknown_cLaunchPadConfig_H

#include "rws/attributes.h"

namespace unknown
{
    class cLaunchPadConfig : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
