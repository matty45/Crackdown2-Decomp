// CD2 constructor 0x826107F8 confirms the shared base constructor chain.
#include "Equip/cCWWeapon.h"
#include "Equip/cRefractorBeam.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cRefractor (Crackdown 2): STAND-IN: constructor-confirmed base and beam member (RuffKing m_Beam;
// CD2's constructor 0x826107F8 builds it at +0xA10 and its deleting destructor 0x826108D8 destroys it).
// StaticCreateClass (0x82610758) builds cClass(0x27415, "cRefractor", 0xA60); 0xA60 is the size its registrar gives.
#ifndef EQUIP_CREFRACTOR_H
#define EQUIP_CREFRACTOR_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cRefractor : public Equip::cCWWeapon
    {
    public:
        // CD2 factory 0x82610740 forwards only this, without a prototype argument.
        cRefractor();
        // CD2 0x826105E0: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x826105F0: registered-class virtual slot 1.
        virtual bool IsA(const Fun_Runtime::cClass &c) const;
        // CD2 0x82610730: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FCD710 names placement factory 0x82610740.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcRefractorClass;
        static Fun_Runtime::cClass &StaticCreateClass();

    private:
        cRefractorBeam m_Beam;

        // CD2: cRefractor's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual Fun_Runtime::RetVal Init(GOM::cSpawner const *); // 18: 0x82608168
        virtual Fun_Runtime::cScriptTypeRegistration const * RetScriptTypeRegistration() const; // cSafeDeletable 1: 0x82607BD0
    private:
        CD2_LAYOUT_CHECKS(cRefractor,
            CD2_SIZE(cRefractor, 0xA60)
            CD2_OFFSET(cRefractor, m_Beam, 0xA10))

    public:
        // CD2 table 0x82121FC0 differs from cCWWeapon at these inherited slots.
        virtual void vf378(); // slot 378: 0x82610978
        virtual void vf408(); // slot 408: 0x826182E8
    };
}

#endif // EQUIP_CREFRACTOR_H
