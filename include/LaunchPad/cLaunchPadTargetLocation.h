#ifndef LaunchPad_cLaunchPadTargetLocation_H
#define LaunchPad_cLaunchPadTargetLocation_H

#include "rws/attributes.h"

namespace LaunchPad
{
    class cLaunchPadTargetLocation : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
