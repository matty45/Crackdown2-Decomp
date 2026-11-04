#include "cd2/layout.h"
#include "Prop/cPrismaticProp.h"
#include "rws/attributes.h"
// unknown::cAgencyGaragePlatform (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x827363B0) builds cClass(0x1024, "cAgencyGaragePlatform", 0xEE0); 0xEE0 is the size its registrar gives.
#ifndef UNKNOWN_CAGENCYGARAGEPLATFORM_H
#define UNKNOWN_CAGENCYGARAGEPLATFORM_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cAgencyGaragePlatform
    {
    public:
        // CD2 MakeNew (0x82736250) allocates 0x530 bytes, calls Prop::cPrismaticProp::cPrismaticPropPrototype's constructor (0x8273CBD0) with the packet and
        // installs this prototype's vtables (at 0 and 0x18).
        class cAgencyGaragePlatformPrototype : public Prop::cPrismaticProp::cPrismaticPropPrototype
        {
        public:
            // __forceinline: CD2 inlines this constructor into MakeNew (docs/matching-notes.md, "Inlining").
            __forceinline cAgencyGaragePlatformPrototype(const RWS::CAttributePacket &packet) : Prop::cPrismaticProp::cPrismaticPropPrototype(packet) {}

            CD2_LAYOUT_CHECKS(cAgencyGaragePlatformPrototype, CD2_SIZE(cAgencyGaragePlatformPrototype, 0x530))
        };

        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcAgencyGaragePlatformClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CAGENCYGARAGEPLATFORM_H
