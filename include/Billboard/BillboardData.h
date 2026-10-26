#ifndef Billboard_BillboardData_H
#define Billboard_BillboardData_H

#include "rws/attributes.h"

namespace Billboard
{
    class BillboardData : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
