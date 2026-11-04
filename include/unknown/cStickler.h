#include "gom/object_prototype.h"
#include "rws/attributes.h"
// unknown::cStickler (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82622FB0) builds cClass(0x10142, "cStickler", 0xAE0); 0xAE0 is the size its registrar gives.
#ifndef UNKNOWN_CSTICKLER_H
#define UNKNOWN_CSTICKLER_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cStickler
    {
    public:
        // CD2 0x82622EC8: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FD10A8 names placement factory 0x82622ed8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcSticklerClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CSTICKLER_H
