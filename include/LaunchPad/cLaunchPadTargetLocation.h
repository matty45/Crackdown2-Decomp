#ifndef LaunchPad_cLaunchPadTargetLocation_H
#define LaunchPad_cLaunchPadTargetLocation_H

#include "rws/attributes.h"

namespace LaunchPad
{
    class cLaunchPadTargetLocation : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
