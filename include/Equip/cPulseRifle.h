#include "Equip/cCWWeapon.h"
#include "Equip/cPulse.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cPulseRifle (Crackdown 2): RuffKing's base (cCWWeapon), pulse member and overrides. StaticCreateClass
// (0x8260FAA0) builds cClass(0x27413, "cPulseRifle", 0xA80); 0xA80 is the size its registrar gives. Its placement
// factory (0x8260ED48) runs cCWWeapon's constructor (0x82607FC8, this only), installs the ten tables and builds the
// pulse at +0xA10 (RuffKing's cCWWeapon is 0xB0 larger: m_Pulse is at 0xAC0 there).
#ifndef EQUIP_CPULSERIFLE_H
#define EQUIP_CPULSERIFLE_H

#include "fun_runtime/class.h"
#include "Equip/tPulseProfile.h"

namespace Equip
{
    class cPulseRifle : public cCWWeapon
    {
    public:
        // RuffKing prototype name/base; CD2 Init is primary slot 5 (0x8260EE18).
        // CD2's MakeNew (0x8260ECE0) allocates 0x430 and calls the constructor (0x8260FEA8) out of line.
        class cPulseRiflePrototype : public cCWWeapon::cCWWeaponPrototype
        {
        public:
            cPulseRiflePrototype(const RWS::CAttributePacket &);
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
            virtual void HandleAttributes(const RWS::CAttributePacket &);

            tPulseProfile m_PulseProfile;
            float m_fPulseAISoundRadius;

            CD2_LAYOUT_CHECKS(cPulseRiflePrototype,
                CD2_SIZE(cPulseRiflePrototype, 0x430)
                CD2_OFFSET(cPulseRiflePrototype, m_PulseProfile, 0x3E0)
                CD2_OFFSET(cPulseRiflePrototype, m_fPulseAISoundRadius, 0x420))
        };

        // CD2's placement factory (0x8260ED48) expands this constructor; RuffKing's takes the prototype, which CD2's
        // base construction does not pass.
        __forceinline cPulseRifle() {}
        // CD2 0x8260ED38: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 0x8260EC70 / 0x8260EC80: the registered-class pair, at the start of this object's code.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        // CD2 spawning initializer 0x82FCD2D8 names placement factory 0x8260ed48.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcPulseRifleClass;
        static Fun_Runtime::cClass &StaticCreateClass();

    protected:
        // RuffKing's overrides; CD2's primary table 0x821217E0 differs from cCWWeapon's 0x820133D0 at these slots.
        virtual void TickUpdate(float fDeltaTime); // slot 23: 0x8260FBA0
        virtual bool BeginAttack(); // slot 378: 0x8260FBE0
        virtual void UpdateAttachedMuzzleEffect(); // slot 408: 0x826182E8, cRefractor's folded body

    private:
        cPulse m_Pulse;

        CD2_LAYOUT_CHECKS(cPulseRifle,
            CD2_SIZE(cPulseRifle, 0xA80)
            CD2_OFFSET(cPulseRifle, m_Pulse, 0xA10))
    };
}

#endif // EQUIP_CPULSERIFLE_H
