#ifndef AI_cTrainingTrigger_H
#define AI_cTrainingTrigger_H

#include "rws/attributes.h"

namespace AI
{
    class cTrainingTrigger : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
