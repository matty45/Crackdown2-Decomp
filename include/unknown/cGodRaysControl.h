#ifndef unknown_cGodRaysControl_H
#define unknown_cGodRaysControl_H

#include "rws/attributes.h"

namespace unknown
{
    class cGodRaysControl : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
