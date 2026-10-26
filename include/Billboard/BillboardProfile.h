#ifndef Billboard_BillboardProfile_H
#define Billboard_BillboardProfile_H

#include "rws/attributes.h"

namespace Billboard
{
    class BillboardProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
