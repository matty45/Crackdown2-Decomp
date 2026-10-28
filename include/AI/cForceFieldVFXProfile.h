#ifndef AI_cForceFieldVFXProfile_H
#define AI_cForceFieldVFXProfile_H

#include "rws/attributes.h"
#include "cd2/layout.h"

namespace AI
{
    class cForceFieldVFXProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif
