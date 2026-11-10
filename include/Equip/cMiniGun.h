#include "Equip/cCWFirearm.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cMiniGun (Crackdown 2): STAND-IN; derived storage is not modelled yet.
// Base cCWFirearm: the destructor 0x8263B410 calls cCWFirearm's (0x82617EB8).
// StaticCreateClass (0x8263B320) builds cClass(0x13268, "cMiniGun", 0xAC0); 0xAC0 is the size its registrar gives.
#ifndef EQUIP_CMINIGUN_H
#define EQUIP_CMINIGUN_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cMiniGun : public cCWFirearm
    {
    public:
        // Inline: CD2's placement factory (0x8263B250) calls cCWFirearm's (0x821F0768) constructor, then stores this class's vptrs.
        __forceinline cMiniGun() : m_fBarrelSpeed(0.0f) {}
        // CD2 0x8263B240: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 0x8263B410.
        virtual ~cMiniGun();
        // CD2 spawning initializer 0x82FD4718 names placement factory 0x8263b250.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcMiniGunClass;
        static Fun_Runtime::cClass &StaticCreateClass();

    private:
        float m_fBarrelSpeed;                      // 0xAB0 (RuffKing's name)
        unsigned char m_unmodelledAB4[0xAC0 - 0xAB4];

        // CD2: cMiniGun's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Slot23(); // 23: 0x8263B4B8
        virtual Fun_Runtime::cClass const & RetClass() const; // cBody 0: 0x8263BA60
        virtual bool IsA(Fun_Runtime::cClass const &) const; // cBody 1: 0x8263BA10
    private:
        CD2_LAYOUT_CHECKS(cMiniGun,
            CD2_SIZE(cMiniGun, 0xAC0))
    };
}

#endif // EQUIP_CMINIGUN_H
