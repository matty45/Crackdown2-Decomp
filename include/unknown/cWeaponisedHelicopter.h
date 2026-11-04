#include "gom/object_prototype.h"
#include "rws/attributes.h"
// unknown::cWeaponisedHelicopter (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x826E19C8) builds cClass(0x4C70, "cWeaponisedHelicopter", 0x2DB0); 0x2DB0 is the size its registrar gives.
#ifndef UNKNOWN_CWEAPONISEDHELICOPTER_H
#define UNKNOWN_CWEAPONISEDHELICOPTER_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cWeaponisedHelicopter
    {
    public:
        // CD2 0x826E1800: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
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
