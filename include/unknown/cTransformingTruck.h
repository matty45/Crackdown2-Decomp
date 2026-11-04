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
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcTransformingTruckClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CTRANSFORMINGTRUCK_H
