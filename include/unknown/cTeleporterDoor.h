#include "Prop/cPrismaticProp.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// unknown::cTeleporterDoor (Crackdown 2): STAND-IN; derived storage is not modelled yet.
// Base cPrismaticProp: the destructor 0x82740B40 calls cPrismaticProp's (0x8273BC98).
// StaticCreateClass (0x82740A58) builds cClass(0x1022, "cTeleporterDoor", 0xEF0); 0xEF0 is the size its registrar gives.
#ifndef UNKNOWN_CTELEPORTERDOOR_H
#define UNKNOWN_CTELEPORTERDOOR_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cTeleporterDoor : public Prop::cPrismaticProp
    {
    public:
        // CD2 0x82740960: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 0x82740B40.
        virtual ~cTeleporterDoor();
        // CD2 spawning initializer 0x82FF99D0 names placement factory 0x82740970.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcTeleporterDoorClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CTELEPORTERDOOR_H
