#include "gom/object_prototype.h"
#include "rws/attributes.h"
#include "Vehicle/cHelicopter.h"
// unknown::cWeaponisedHelicopter (Crackdown 2): STAND-IN. Base cHelicopter (its inheritance registrar); the registrar size is
// cHelicopter's (0x2DB0), so it adds no fields.
// StaticCreateClass (0x826E19C8) builds cClass(0x4C70, "cWeaponisedHelicopter", 0x2DB0); 0x2DB0 is the size its registrar gives.
#ifndef UNKNOWN_CWEAPONISEDHELICOPTER_H
#define UNKNOWN_CWEAPONISEDHELICOPTER_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cWeaponisedHelicopter : public Vehicle::cHelicopter
    {
    public:
        // Prototype name ours. CD2's MakeNew (0x826E1870) allocates 0x4D0, calls cHeliPrototype's constructor
        // (0x826B8D10) and stores this class's vptrs: the constructor is inline and initializes none of its own fields.
        class cWeaponisedHelicopterPrototype : public Vehicle::cHelicopter::cHeliPrototype
        {
        public:
            __forceinline cWeaponisedHelicopterPrototype(const RWS::CAttributePacket &packet)
                : Vehicle::cHelicopter::cHeliPrototype(packet) {}

        private:
            unsigned char m_unmodelled4C0[0x4D0 - 0x4C0];

            CD2_LAYOUT_CHECKS(cWeaponisedHelicopterPrototype,
                CD2_SIZE(cWeaponisedHelicopterPrototype, 0x4D0))
        };

        // Inline: CD2's placement factory (0x826E18F0) calls cHelicopter's constructor, then stores this class's vptrs.
        __forceinline cWeaponisedHelicopter() {}
        // CD2 0x826E1AB0: restores this class's vtables, then calls cHelicopter's destructor.
        virtual ~cWeaponisedHelicopter();
        // CD2 0x826E1800: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x826E1810: registered-class virtual slot 1.
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        // CD2 0x826E18E0: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FEA550 names placement factory 0x826e18f0.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcWeaponisedHelicopterClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CWEAPONISEDHELICOPTER_H
