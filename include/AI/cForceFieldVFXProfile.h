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
        // CD2: cForceFieldVFXProfile's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x82488E48
    };
}

#endif
