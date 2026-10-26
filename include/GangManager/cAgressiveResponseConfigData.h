#ifndef GangManager_cAgressiveResponseConfigData_H
#define GangManager_cAgressiveResponseConfigData_H

#include "rws/attributes.h"

namespace GangManager
{
    class cAgressiveResponseConfigData : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
