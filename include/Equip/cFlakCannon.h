#include "Equip/cCWHeavyWeapon.h"
#include <float.h>
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cFlakCannon (Crackdown 2): STAND-IN; derived storage is not modelled yet.
// Base cCWHeavyWeapon: the destructor 0x8263A940 calls cCWHeavyWeapon's (0x8262FCB0).
// StaticCreateClass (0x8263A850) builds cClass(0x13269, "cFlakCannon", 0xA30); 0xA30 is the size its registrar gives.
#ifndef EQUIP_CFLAKCANNON_H
#define EQUIP_CFLAKCANNON_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cFlakCannon : public cCWHeavyWeapon
    {
    public:
        // Inline: CD2's placement factory (0x8263A780) calls cCWHeavyWeapon's (0x8262FF78) constructor, then stores this class's vptrs.
        __forceinline cFlakCannon() : m_fAnimStartTime(FLT_MAX) {}
        // Name and base from RuffKing. CD2's MakeNew (0x8263A718) allocates 0x430 and calls the constructor
        // (0x8263AD00) out of line, which calls cCWHeavyWeaponPrototype's (0x82630920); own fields are not recovered.
        class cFlakCannonPrototype : public cCWHeavyWeapon::cCWHeavyWeaponPrototype
        {
        public:
            cFlakCannonPrototype(const RWS::CAttributePacket &);

        private:
            unsigned char m_unmodelled410[0x430 - 0x410];

            CD2_LAYOUT_CHECKS(cFlakCannonPrototype,
                CD2_SIZE(cFlakCannonPrototype, 0x430))
        };

        // CD2 0x8263A770: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 0x8263A940.
        virtual ~cFlakCannon();
        // CD2 spawning initializer 0x82FD4368 names placement factory 0x8263a780.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcFlakCannonClass;
        static Fun_Runtime::cClass &StaticCreateClass();

    private:
        float m_fAnimStartTime;                    // 0xA20 (RuffKing's name)
        unsigned char m_unmodelledA24[0xA30 - 0xA24];

        CD2_LAYOUT_CHECKS(cFlakCannon,
            CD2_SIZE(cFlakCannon, 0xA30))
    };
}

#endif // EQUIP_CFLAKCANNON_H
