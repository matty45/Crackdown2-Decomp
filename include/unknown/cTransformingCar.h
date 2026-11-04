#include "gom/object_prototype.h"
#include "rws/attributes.h"
// unknown::cTransformingCar (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x826AB6D8) builds cClass(0x14, "cTransformingCar", 0x67D0); 0x67D0 is the size its registrar gives.
#ifndef UNKNOWN_CTRANSFORMINGCAR_H
#define UNKNOWN_CTRANSFORMINGCAR_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cTransformingCar
    {
    public:
        // CD2 0x826AB518: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FE7220 names placement factory 0x826ab528.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcTransformingCarClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CTRANSFORMINGCAR_H
