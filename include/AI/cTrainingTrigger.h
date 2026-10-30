#ifndef AI_cTrainingTrigger_H
#define AI_cTrainingTrigger_H

#include "rws/attributes.h"

namespace AI
{
    class cTrainingTrigger : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
