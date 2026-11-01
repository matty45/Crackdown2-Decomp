#ifndef VFX_cPostProcessControl_H
#define VFX_cPostProcessControl_H

#include "rws/attributes.h"

namespace VFX
{
    class cPostProcessControl : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
