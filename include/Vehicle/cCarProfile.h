#ifndef Vehicle_cCarProfile_H
#define Vehicle_cCarProfile_H

#include "rws/attributes.h"

namespace Vehicle
{
    class cCarProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
