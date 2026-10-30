#ifndef PHYSICS_cSurfaceProfile_H
#define PHYSICS_cSurfaceProfile_H

#include "rws/attributes.h"

namespace PHYSICS
{
    class cSurfaceProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
