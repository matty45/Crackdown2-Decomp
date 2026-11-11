#include "Equip/cExplosiveGrenade.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// unknown::cSticklerGrenade (Crackdown 2): STAND-IN; derived storage is not modelled yet.
// Base cExplosiveGrenade: the destructor 0x82623420 calls cExplosiveGrenade's (0x8261D3F0).
// StaticCreateClass (0x82623330) builds cClass(0x10144, "cSticklerGrenade", 0x9E0); 0x9E0 is the size its registrar gives.
#ifndef UNKNOWN_CSTICKLERGRENADE_H
#define UNKNOWN_CSTICKLERGRENADE_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cSticklerGrenade : public Equip::cExplosiveGrenade
    {
    public:
        // CD2 0x82623320: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        // CD2 0x82623240: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 0x82623420.
        virtual ~cSticklerGrenade();
        // CD2 spawning initializer 0x82FD14E0 names placement factory 0x82623250.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcSticklerGrenadeClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        // CD2: cSticklerGrenade's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual Fun_Runtime::RetVal Init(GOM::cSpawner const *); // 18: 0x826234C0
        virtual void Slot23(); // 23: 0x82623758
        virtual void Slot24(); // 24: 0x826237B8
        virtual void vf76(); // 76: 0x82623BC0
        virtual void vf158(); // 158: 0x82623810
        virtual void vf199(); // 199: 0x82623B40
        virtual void vf284(); // 284: 0x82623B60
        virtual Fun_Runtime::cClass const & RetClass() const; // cBody 0: 0x82623E38
        virtual bool IsA(Fun_Runtime::cClass const &) const; // cBody 1: 0x82623E40

    public:
        // CD2 table 0x82125FA0 differs from cExplosiveGrenade at these inherited slots.
        virtual void vf406(); // slot 406: 0x82623538
        virtual void vf416(); // slot 416: 0x82623A38
        virtual void vf426(); // slot 426: 0x827E56A8
    };
}

#endif // UNKNOWN_CSTICKLERGRENADE_H
