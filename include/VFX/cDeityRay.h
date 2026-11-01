#ifndef VFX_cDeityRay_H
#define VFX_cDeityRay_H

#include "rws/attributes.h"

namespace VFX
{
    class cDeityRay : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
