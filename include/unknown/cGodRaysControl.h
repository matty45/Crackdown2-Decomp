#ifndef unknown_cGodRaysControl_H
#define unknown_cGodRaysControl_H

#include "rws/attributes.h"

namespace unknown
{
    class cGodRaysControl : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
