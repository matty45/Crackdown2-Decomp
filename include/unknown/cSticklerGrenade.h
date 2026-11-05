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
    };
}

#endif // UNKNOWN_CSTICKLERGRENADE_H
