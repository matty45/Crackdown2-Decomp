#ifndef Vehicle_cHelicopter_H
#define Vehicle_cHelicopter_H

#include "gom/object_prototype.h"
#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace Vehicle
{
    class cHelicopter : public RWS::CAttributeHandler
    {
    public:
        // Out of line: CD2 tail-calls it from SpawnFromPrototype.
        cHelicopter();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static const Fun_Runtime::cClass *ms_pcHelicopterClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
