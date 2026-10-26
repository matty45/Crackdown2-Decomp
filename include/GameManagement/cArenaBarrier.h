#ifndef GameManagement_cArenaBarrier_H
#define GameManagement_cArenaBarrier_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cArenaBarrier : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
