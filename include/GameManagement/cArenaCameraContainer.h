#ifndef GameManagement_cArenaCameraContainer_H
#define GameManagement_cArenaCameraContainer_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cArenaCameraContainer : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
