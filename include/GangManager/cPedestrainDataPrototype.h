#ifndef GangManager_cPedestrainDataPrototype_H
#define GangManager_cPedestrainDataPrototype_H

#include "rws/attributes.h"

namespace GangManager
{
    class cPedestrainDataPrototype : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
