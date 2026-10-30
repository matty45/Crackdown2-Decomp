#ifndef unknown_cCrowdManager_H
#define unknown_cCrowdManager_H

#include "rws/attributes.h"

namespace unknown
{
    class cCrowdManager : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
