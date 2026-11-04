#include "gom/object_prototype.h"
#ifndef Vehicle_cHelicopter_H
#define Vehicle_cHelicopter_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace Vehicle
{
    class cHelicopter : public RWS::CAttributeHandler
    {
    public:
        // CD2 spawning initializer 0x82FE85A0 names placement factory 0x826b8ae0.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static const Fun_Runtime::cClass *ms_pcHelicopterClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
