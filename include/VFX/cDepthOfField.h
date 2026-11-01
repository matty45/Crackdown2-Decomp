#ifndef VFX_cDepthOfField_H
#define VFX_cDepthOfField_H

#include "rws/attributes.h"

namespace VFX
{
    class cDepthOfField : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
