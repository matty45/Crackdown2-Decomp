#ifndef GameManagement_cCD1Barrier_H
#define GameManagement_cCD1Barrier_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cCD1Barrier : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
