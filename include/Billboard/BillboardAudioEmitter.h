#ifndef Billboard_BillboardAudioEmitter_H
#define Billboard_BillboardAudioEmitter_H

#include "rws/attributes.h"

namespace Billboard
{
    class BillboardAudioEmitter : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
