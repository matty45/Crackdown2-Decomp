#ifndef VFX_cBeamData_H
#define VFX_cBeamData_H

#include "rws/attributes.h"

namespace VFX
{
    class cBeamData : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
