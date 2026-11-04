#ifndef Vehicle_cLandVehicle_H
#define Vehicle_cLandVehicle_H

#include "gom/object_prototype.h"
#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace Vehicle
{
    class cLandVehicle : public RWS::CAttributeHandler
    {
    public:
        // Out of line: CD2 tail-calls it from SpawnFromPrototype.
        cLandVehicle();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static const Fun_Runtime::cClass *ms_pcLandVehicleClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
