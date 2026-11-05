#include "Equip/cGrenade.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// unknown::cBoostPack (Crackdown 2): STAND-IN; derived storage is not modelled yet.
// Base cGrenade: CD2's inheritance registrar names it, and the destructor 0x8260AED8 calls cGrenade's (0x8261E460).
// StaticCreateClass (0x8260ADA0) builds cClass(0x10141, "cBoostPack", 0x9D0); 0x9D0 is the size its registrar gives.
#ifndef UNKNOWN_CBOOSTPACK_H
#define UNKNOWN_CBOOSTPACK_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cBoostPack : public Equip::cGrenade
    {
    public:
        // CD2 0x8260AD38: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        // CD2 0x8260AC58: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 0x8260AED8.
        virtual ~cBoostPack();
        // CD2 spawning initializer 0x82FCC368 names placement factory 0x8260ac68.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcBoostPackClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CBOOSTPACK_H
