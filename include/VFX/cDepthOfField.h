#ifndef VFX_cDepthOfField_H
#define VFX_cDepthOfField_H

#include "rws/attributes.h"

namespace VFX
{
    class cDepthOfField : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
