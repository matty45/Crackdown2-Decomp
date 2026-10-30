#ifndef Vehicle_cLandVehicle_H
#define Vehicle_cLandVehicle_H

#include "rws/attributes.h"

namespace Vehicle
{
    class cLandVehicle : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
