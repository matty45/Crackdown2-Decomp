#include "cd2/layout.h"
#include "Prop/cPrismaticProp.h"
#include "rws/attributes.h"
// unknown::cTeleporterDoor (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82740A58) builds cClass(0x1022, "cTeleporterDoor", 0xEF0); 0xEF0 is the size its registrar gives.
#ifndef UNKNOWN_CTELEPORTERDOOR_H
#define UNKNOWN_CTELEPORTERDOOR_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cTeleporterDoor
    {
    public:
        // CD2 MakeNew (0x827408f0) allocates 0x530 bytes, calls Prop::cPrismaticProp::cPrismaticPropPrototype's constructor (0x8273CBD0) with the packet and
        // installs this prototype's vtables (at 0 and 0x18).
        class cTeleporterDoorPrototype : public Prop::cPrismaticProp::cPrismaticPropPrototype
        {
        public:
            // __forceinline: CD2 inlines this constructor into MakeNew (docs/matching-notes.md, "Inlining").
            __forceinline cTeleporterDoorPrototype(const RWS::CAttributePacket &packet) : Prop::cPrismaticProp::cPrismaticPropPrototype(packet) {}

            CD2_LAYOUT_CHECKS(cTeleporterDoorPrototype, CD2_SIZE(cTeleporterDoorPrototype, 0x530))
        };

        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcTeleporterDoorClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CTELEPORTERDOOR_H
