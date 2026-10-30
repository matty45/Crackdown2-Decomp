#ifndef AI_CellGuard_H
#define AI_CellGuard_H

#include "rws/attributes.h"

namespace AI
{
    class CellGuard : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
