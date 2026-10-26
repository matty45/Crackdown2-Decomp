#ifndef GameManagement_cNetGameSpawnPoint_H
#define GameManagement_cNetGameSpawnPoint_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cNetGameSpawnPoint : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
