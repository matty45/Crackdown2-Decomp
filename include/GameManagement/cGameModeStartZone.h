#ifndef GameManagement_cGameModeStartZone_H
#define GameManagement_cGameModeStartZone_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cGameModeStartZone : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
