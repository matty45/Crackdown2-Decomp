#ifndef GangManager_cTurretDataPrototype_H
#define GangManager_cTurretDataPrototype_H

#include "rws/attributes.h"

namespace GangManager
{
    class cTurretDataPrototype : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
