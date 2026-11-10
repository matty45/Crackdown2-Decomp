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
        // CD2: cDelugeKillScoreOverride's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x828637A8
    };
}

#endif
