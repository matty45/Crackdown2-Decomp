#ifndef GameManagement_cStreamedArenaConfig_H
#define GameManagement_cStreamedArenaConfig_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cStreamedArenaConfig : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
