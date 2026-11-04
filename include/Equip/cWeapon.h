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
        // Interface-only prototype stand-in: name and base from RuffKing.
        // Instance fields and complete size are not recovered; this is not an allocation layout.
        class cWeaponPrototype : public cEquipment::cEquipmentPrototype {};

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
