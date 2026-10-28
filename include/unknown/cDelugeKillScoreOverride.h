#ifndef unknown_cDelugeKillScoreOverride_H
#define unknown_cDelugeKillScoreOverride_H

#include "rws/attributes.h"

namespace unknown
{
    class cDelugeKillScoreOverride : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif
