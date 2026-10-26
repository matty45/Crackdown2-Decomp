#ifndef GameManagement_cDeathMatchGameModePrototype_H
#define GameManagement_cDeathMatchGameModePrototype_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cDeathMatchGameModePrototype : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
