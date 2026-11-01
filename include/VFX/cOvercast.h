#ifndef VFX_cOvercast_H
#define VFX_cOvercast_H

#include "rws/attributes.h"

namespace VFX
{
    class cOvercast : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
