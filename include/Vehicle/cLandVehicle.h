#ifndef Vehicle_cLandVehicle_H
#define Vehicle_cLandVehicle_H

#include "cd2/layout.h"
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
    public:
        // Out of line: CD2 0x826C6B90 (MakeNew calls it with the packet).
        cLandVehicle(const RWS::CAttributePacket &packet);

    private:
        unsigned char m_unmodelled18[0x440 - 0x18];

        CD2_LAYOUT_CHECKS(cLandVehicle, CD2_SIZE(cLandVehicle, 0x440))

    };
}

#endif
