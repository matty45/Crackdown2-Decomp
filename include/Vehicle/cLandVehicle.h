#ifndef Vehicle_cLandVehicle_H
#define Vehicle_cLandVehicle_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace Vehicle
{
    class cLandVehicle : public RWS::CAttributeHandler
    {
    public:
        static const Fun_Runtime::cClass *ms_pcLandVehicleClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
