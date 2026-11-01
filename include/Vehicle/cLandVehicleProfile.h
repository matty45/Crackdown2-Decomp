#ifndef Vehicle_cLandVehicleProfile_H
#define Vehicle_cLandVehicleProfile_H

#include "rws/attributes.h"

namespace Vehicle
{
    class cLandVehicleProfile : public RWS::CAttributeHandler
    {
    public:
        // CD2 0x8269FA58: attribute-handler vtable slot 6, returning Ret_OK.
        virtual Fun_Runtime::RetVal Term();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
