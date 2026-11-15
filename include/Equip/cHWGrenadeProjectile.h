#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cHWGrenadeProjectile (Crackdown 2): STAND-IN for the class name only. Base Equip::cHWProjectile, as in
// RuffKing's header; RetClassName (0x82629390) is slot 11 of the vtable at 0x82127130, as cNonGameBase's RetClassName.
#ifndef EQUIP_CHWGRENADEPROJECTILE_H
#define EQUIP_CHWGRENADEPROJECTILE_H

#include "Equip/cFlocket.h"
#include "Audio/cPhysicsBodyGameObject.h"
#include "cd2/layout.h"
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
        // CD2 0x82629280 / 0x82629290: the registered-class pair, at the start of this object's code.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        // CD2 0x82629658 (its deleting destructor 0x82629608 calls it): terminates the audio object, then destroys it
        // and cHWProjectile.
        virtual ~cHWGrenadeProjectile();

        // CD2 table 0x82127130 (stored by the destructor) differs from cHWProjectile's 0x82127898 at these slots too;
        // names and signatures are the bases'.
        virtual void Slot13();                                                                     // 13: 0x82629720
        virtual void vf158();                                                                      // 158: 0x82629C70
        virtual void ImpactAudio(float fDeltaVelocity);                                            // 258: 0x82629C50
        virtual int RetNetworkLOD(CHARACTER::cCharacter *, int);                                   // 350: 0x82629C68
        virtual void EventCollision(PHYSICS::cBody *pBody, const PHYSICS::cCustomMaterial &material,
                                    const Fun_Runtime::Vec3 &vHitPos, const Fun_Runtime::Vec3 &vHitNormal);   // 364: 0x826297D0
        virtual void Launch(float fInitProjectileVel, const Fun_Runtime::Vec3 &vecTargetPoint, float fAccuracy); // 366: 0x82629F00
        virtual void UpdateExplosionTimer(float dT);                                               // 369: 0x82629CF8
        virtual int SetupCollisionFilter();                                                        // 371: 0x82629798

    private:
        // RuffKing's member, at the end of cHWProjectile (0x970) in CD2; descriptor size 0xA40.
        Audio::cPhysicsBodyGameObject m_GrenadePhysicsAudio;    // 0x970
        unsigned char m_unmodelledA38[0xA40 - 0xA38];

        CD2_LAYOUT_CHECKS(cHWGrenadeProjectile,
            CD2_SIZE(cHWGrenadeProjectile, 0xA40)
            CD2_OFFSET(cHWGrenadeProjectile, m_GrenadePhysicsAudio, 0x970))
    };
}

#endif // EQUIP_CHWGRENADEPROJECTILE_H
