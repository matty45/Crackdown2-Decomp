#ifndef unknown_cLaunchPadLocation_H
#define unknown_cLaunchPadLocation_H

#include "rws/attributes.h"

namespace unknown
{
    class cLaunchPadLocation : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
