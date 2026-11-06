#include "Prop/cPrismaticProp.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// unknown::cWeaponCabinetDoor (Crackdown 2): STAND-IN; derived storage is not modelled yet.
// Base cPrismaticProp: CD2's inheritance registrar names it, and the destructor 0x827411E8 calls cPrismaticProp's (0x8273BC98).
// StaticCreateClass (0x82741100) builds cClass(0x1021, "cWeaponCabinetDoor", 0xEE0); 0xEE0 is the size its registrar gives.
#ifndef UNKNOWN_CWEAPONCABINETDOOR_H
#define UNKNOWN_CWEAPONCABINETDOOR_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cWeaponCabinetDoor : public Prop::cPrismaticProp
    {
    public:
        // Prototype name ours, from cWeaponCabinetDoor::MakeNew (0x82740FA8).
        // CD2 confirms the shared parent constructor and Init slot 5 (0x82741570).
        // MakeNew allocates 0x540 and inlines the constructor over cPrismaticPropPrototype's (0x8273CBD0); it initializes
        // none of the prototype's own fields, which are not recovered.
        class cWeaponCabinetDoorPrototype : public Prop::cPrismaticProp::cPrismaticPropPrototype
        {
        public:
            __forceinline cWeaponCabinetDoorPrototype(const RWS::CAttributePacket &packet)
                : Prop::cPrismaticProp::cPrismaticPropPrototype(packet) {}
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);

        private:
            unsigned char m_unmodelled530[0x540 - 0x530];

            CD2_LAYOUT_CHECKS(cWeaponCabinetDoorPrototype,
                CD2_SIZE(cWeaponCabinetDoorPrototype, 0x540))
        };

        // CD2 0x82740F38: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x82740F48: registered-class virtual slot 1.
        virtual bool IsA(const Fun_Runtime::cClass &c) const;
        // CD2 0x827411E8.
        virtual ~cWeaponCabinetDoor();
        // CD2 0x82741018: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FF9E08 names placement factory 0x82741028.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcWeaponCabinetDoorClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CWEAPONCABINETDOOR_H
