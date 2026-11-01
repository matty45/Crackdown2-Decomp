#ifndef VFX_cSkyDome_H
#define VFX_cSkyDome_H

#include "rws/attributes.h"

namespace VFX
{
    class cSkyDome : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
