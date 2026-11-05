#include "Prop/cPrismaticProp.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// unknown::cAgencyGaragePlatform (Crackdown 2): STAND-IN; derived storage is not modelled yet.
// Base cPrismaticProp: the destructor 0x82736538 calls cPrismaticProp's (0x8273BC98).
// StaticCreateClass (0x827363B0) builds cClass(0x1024, "cAgencyGaragePlatform", 0xEE0); 0xEE0 is the size its registrar gives.
#ifndef UNKNOWN_CAGENCYGARAGEPLATFORM_H
#define UNKNOWN_CAGENCYGARAGEPLATFORM_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cAgencyGaragePlatform : public Prop::cPrismaticProp
    {
    public:
        // CD2 0x827362C0: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 0x82736538.
        virtual ~cAgencyGaragePlatform();
        // CD2 spawning initializer 0x82FF6CA0 names placement factory 0x827362d0.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcAgencyGaragePlatformClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CAGENCYGARAGEPLATFORM_H
