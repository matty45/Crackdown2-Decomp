#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cHWGrenadeProjectile (Crackdown 2): STAND-IN for the class name only. Base Equip::cHWProjectile, as in
// RuffKing's header; RetClassName (0x82629390) is slot 11 of the vtable at 0x82127130, as cNonGameBase's RetClassName.
#ifndef EQUIP_CHWGRENADEPROJECTILE_H
#define EQUIP_CHWGRENADEPROJECTILE_H

#include "Equip/cFlocket.h"
namespace Fun_Runtime { template <class T> class cScriptTypeRegistrar; }

namespace Equip
{
    class cHWGrenadeProjectile : public Equip::cHWProjectile
    {
    protected:
        // CD2 primary slot 375 is the first virtual added after cHWProjectile;
        // registrar 0x82629468 names it HasExploded (native vcall thunk 0x827450B0).
        virtual bool HasExploded();
        // CD2 table 0x82127130 slot 330 overrides the inherited equipment query.
        virtual bool IsLive();
        // The registrar is the observed external address-taking user of these
        // queries; their protected access follows the reference header.
        friend class Fun_Runtime::cScriptTypeRegistrar<cHWGrenadeProjectile>;
    public:
        // CD2 0x826293C0: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        // CD2 spawning initializer 0x82FD2320 names placement factory 0x826293a0.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 0x82629500: the placement factory (0x826293A0) calls it out of line with the prototype.
        cHWGrenadeProjectile(GOM::cObjectPrototype *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcHWGrenadeProjectileClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // EQUIP_CHWGRENADEPROJECTILE_H
