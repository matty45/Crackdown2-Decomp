#ifndef VEHICLE_CTRUCK_H
#define VEHICLE_CTRUCK_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"

namespace Vehicle
{
    class cTruck : public cNonGameBase
    {
    public:
        cTruck();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcTruckClass;

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    };
}

#endif

