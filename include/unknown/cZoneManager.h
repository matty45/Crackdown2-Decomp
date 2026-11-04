#include "rws/attributes.h"
// unknown::cZoneManager (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8280B9D8) builds cClass(0x60E, "cZoneManager", 0x84); 0x84 is the size its registrar gives.
#ifndef UNKNOWN_CZONEMANAGER_H
#define UNKNOWN_CZONEMANAGER_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cZoneManager
    {
    public:
        virtual const char *RetClassName() const;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcZoneManagerClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CZONEMANAGER_H
