#ifndef VFX_cTracers_H
#define VFX_cTracers_H

#include "rws/attributes.h"

namespace VFX
{
    class cTracers : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
