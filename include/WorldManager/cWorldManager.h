#ifndef WorldManager_cWorldManager_H
#define WorldManager_cWorldManager_H

#include "rws/attributes.h"

namespace WorldManager
{
    class cWorldManager : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
