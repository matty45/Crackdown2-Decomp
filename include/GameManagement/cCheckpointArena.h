#ifndef GameManagement_cCheckpointArena_H
#define GameManagement_cCheckpointArena_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cCheckpointArena : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
