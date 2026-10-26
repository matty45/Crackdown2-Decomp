#ifndef GameManagement_cCHordeArena_H
#define GameManagement_cCHordeArena_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cCHordeArena : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
