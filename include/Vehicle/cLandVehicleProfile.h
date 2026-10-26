#ifndef Vehicle_cLandVehicleProfile_H
#define Vehicle_cLandVehicleProfile_H

#include "rws/attributes.h"

namespace Vehicle
{
    class cLandVehicleProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
