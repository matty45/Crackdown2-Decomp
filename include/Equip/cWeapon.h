// STAND-IN: RuffKing names cEquipment as the base; CD2 constructor 0x82609AA8
// confirms that constructor chain. Descriptor 0x822E5B60 gives complete size 0x8C0.
// Instance data beyond the recovered base is opaque; no field offsets are inferred from it.
#ifndef EQUIP_CWEAPON_H
#define EQUIP_CWEAPON_H
#include "Equip/cEquipment.h"
namespace Equip
{
    class cWeapon : public cEquipment
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // Interface-only prototype stand-in: name and base from RuffKing.
        // Instance fields and complete size are not recovered; this is not an allocation layout.
        // Name and base from RuffKing. CD2's constructor (0x8260A370) calls cEquipmentPrototype's and initializes
        // 0x29C..0x34B; cGrenadePrototype's constructor (0x8261F758) starts its own fields at 0x350.
        class cWeaponPrototype : public cEquipment::cEquipmentPrototype
        {
        public:
            cWeaponPrototype(const RWS::CAttributePacket &);

        private:
            unsigned char m_unmodelled2F0[0x350 - 0x2F0];

            CD2_LAYOUT_CHECKS(cWeaponPrototype,
                CD2_SIZE(cWeaponPrototype, 0x350))
        };

        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcWeaponClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
    private:
        unsigned char m_unmodelled870[0x8C0 - 0x870];
        CD2_LAYOUT_CHECKS(cWeapon, CD2_SIZE(cWeapon, 0x8C0))
    };
}
#endif
