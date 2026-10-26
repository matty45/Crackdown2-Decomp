#ifndef VFX_cVFXPriorityTable_H
#define VFX_cVFXPriorityTable_H

#include "rws/attributes.h"

namespace VFX
{
    class cVFXPriorityTable : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
