#ifndef GameManagement_cTrainingRespawnPoint_H
#define GameManagement_cTrainingRespawnPoint_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cTrainingRespawnPoint : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
