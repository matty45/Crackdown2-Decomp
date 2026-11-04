#include "cd2/layout.h"
#include "Prop/cPrismaticProp.h"
#include "rws/attributes.h"
// unknown::cWeaponCabinetDoor (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82741100) builds cClass(0x1021, "cWeaponCabinetDoor", 0xEE0); 0xEE0 is the size its registrar gives.
#ifndef UNKNOWN_CWEAPONCABINETDOOR_H
#define UNKNOWN_CWEAPONCABINETDOOR_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cWeaponCabinetDoor
    {
    public:
        // CD2 MakeNew (0x82740fa8) allocates 0x540 bytes, calls Prop::cPrismaticProp::cPrismaticPropPrototype's constructor (0x8273CBD0) with the packet and
        // installs this prototype's vtables (at 0 and 0x18).
        class cWeaponCabinetDoorPrototype : public Prop::cPrismaticProp::cPrismaticPropPrototype
        {
        public:
            // __forceinline: CD2 inlines this constructor into MakeNew (docs/matching-notes.md, "Inlining").
            __forceinline cWeaponCabinetDoorPrototype(const RWS::CAttributePacket &packet) : Prop::cPrismaticProp::cPrismaticPropPrototype(packet) {}

        private:
            unsigned char m_pad530[0x540 - 0x530];

            CD2_LAYOUT_CHECKS(cWeaponCabinetDoorPrototype, CD2_SIZE(cWeaponCabinetDoorPrototype, 0x540))
        };

        virtual const char *RetClassName() const;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcWeaponCabinetDoorClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CWEAPONCABINETDOOR_H
