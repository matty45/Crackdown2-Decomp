#include "gom/object_prototype.h"
#ifndef Vehicle_cLandVehicle_H
#define Vehicle_cLandVehicle_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace Vehicle
{
    class cLandVehicle : public RWS::CAttributeHandler
    {
    public:
        // CD2 spawning initializer 0x82FE8A70 names placement factory 0x826c0e20.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static const Fun_Runtime::cClass *ms_pcLandVehicleClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
