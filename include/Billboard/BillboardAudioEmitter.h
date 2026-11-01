#ifndef Billboard_BillboardAudioEmitter_H
#define Billboard_BillboardAudioEmitter_H

#include "rws/attributes.h"

namespace Billboard
{
    class BillboardAudioEmitter : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
