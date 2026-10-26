#ifndef VFX_cBeamData_H
#define VFX_cBeamData_H

#include "rws/attributes.h"

namespace VFX
{
    class cBeamData : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
