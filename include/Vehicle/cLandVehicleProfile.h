#ifndef Vehicle_cLandVehicleProfile_H
#define Vehicle_cLandVehicleProfile_H

#include "rws/attributes.h"

namespace Vehicle
{
    class cLandVehicleProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
