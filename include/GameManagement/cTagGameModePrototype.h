#ifndef GameManagement_cTagGameModePrototype_H
#define GameManagement_cTagGameModePrototype_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cTagGameModePrototype : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
