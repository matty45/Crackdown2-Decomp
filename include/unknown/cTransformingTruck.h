#include "gom/object_prototype.h"
#include "rws/attributes.h"
// unknown::cTransformingTruck (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x826B1D00) builds cClass(0x15, "cTransformingTruck", 0x69E0); 0x69E0 is the size its registrar gives.
#ifndef UNKNOWN_CTRANSFORMINGTRUCK_H
#define UNKNOWN_CTRANSFORMINGTRUCK_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cTransformingTruck
    {
    public:
        // CD2 0x826B1BF0: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FE76F8 names placement factory 0x826b1c00.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcTransformingTruckClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CTRANSFORMINGTRUCK_H
