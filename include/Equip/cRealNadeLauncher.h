#include "Equip/cCWHeavyWeapon.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cRealNadeLauncher (Crackdown 2): STAND-IN; derived storage is not modelled yet.
// Base cCWHeavyWeapon: CD2's inheritance registrar names it, and the destructor 0x82634BE8 calls cCWHeavyWeapon's (0x8262FCB0).
// StaticCreateClass (0x82634B00) builds cClass(0x6067, "cRealNadeLauncher", 0xA20); 0xA20 is the size its registrar gives.
#ifndef EQUIP_CREALNADELAUNCHER_H
#define EQUIP_CREALNADELAUNCHER_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cRealNadeLauncher : public cCWHeavyWeapon
    {
    public:
        // RuffKing prototype name/base; CD2 Init is primary slot 5 (0x82635418).
        // Interface only: instance fields and allocation size remain unrecovered.
        class cRealNadeLauncherPrototype : public cCWHeavyWeapon::cCWHeavyWeaponPrototype
        {
        public:
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        };

        // CD2 0x82634928: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x82634938: registered-class virtual slot 1.
        virtual bool IsA(const Fun_Runtime::cClass &c) const;
        // CD2 0x82634BE8.
        virtual ~cRealNadeLauncher();
        // CD2 0x82634A28: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FD3B80 names placement factory 0x82634a38.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcRealNadeLauncherClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CREALNADELAUNCHER_H
