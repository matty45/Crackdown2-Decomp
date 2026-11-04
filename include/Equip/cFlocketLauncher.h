#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cFlocketLauncher (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82630F08) builds cClass(0x605F, "cFlocketLauncher", 0xA30); 0xA30 is the size its registrar gives.
#ifndef EQUIP_CFLOCKETLAUNCHER_H
#define EQUIP_CFLOCKETLAUNCHER_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cFlocketLauncher
    {
    public:
        // CD2 0x82630CF0: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x82630E20: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FD33B0 names placement factory 0x82630e30.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcFlocketLauncherClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CFLOCKETLAUNCHER_H
