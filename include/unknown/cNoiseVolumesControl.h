#ifndef unknown_cNoiseVolumesControl_H
#define unknown_cNoiseVolumesControl_H

#include "rws/attributes.h"

namespace unknown
{
    class cNoiseVolumesControl : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
