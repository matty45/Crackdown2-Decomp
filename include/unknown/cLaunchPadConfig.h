#ifndef unknown_cLaunchPadConfig_H
#define unknown_cLaunchPadConfig_H

#include "rws/attributes.h"
#include "cd2/layout.h"

namespace unknown
{
    class cLaunchPadConfig : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif
