#ifndef VFX_cLinkedVFXPrototype_H
#define VFX_cLinkedVFXPrototype_H

#include "rws/attributes.h"

namespace VFX
{
    class cLinkedVFXPrototype : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
