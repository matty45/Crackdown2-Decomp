#ifndef GangManager_cGangInfoPrototype_H
#define GangManager_cGangInfoPrototype_H

#include "rws/attributes.h"

namespace GangManager
{
    class cGangInfoPrototype : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
