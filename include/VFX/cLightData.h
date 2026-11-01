#ifndef VFX_cLightData_H
#define VFX_cLightData_H

#include "rws/attributes.h"

namespace VFX
{
    class cLightData : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
