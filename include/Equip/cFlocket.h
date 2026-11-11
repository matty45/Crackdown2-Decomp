#include "gom/object_prototype.h"
// Equip::cHWProjectile, Equip::cFlocket and their prototypes (Crackdown 2). CD2 object sizes 0x970 and 0x9B0,
// prototypes 0x320 and 0x360.
// cHWProjectile derives from cWeaponProjectile (0x870 bytes) and ExplosionManager::cExplosionCallback, as CD2's
// inheritance registrar (0x82FD26F8) and RuffKing say; its eleven virtuals are RuffKing's, in slots 364 to 374 of
// cFlocket's CD2 table (0x82126830, 375 slots), where UpdateAttachedEffect and ReleaseEffect are the last two.
#ifndef EQUIP_CFLOCKET_H
#define EQUIP_CFLOCKET_H

#include <ppcintrinsics.h>
#include "Network/cPositionalProxy.h"
#include "rws/attributes.h"
#include "rws/classfactory.h"
#include "cd2/layout.h"
#include "cd2/memory.h"
#include "fun_runtime/class.h"
#include "fun_runtime/vec3.h"
#include "gom/non_game_base.h"
#include "Equip/cWeaponProjectile.h"
#include "ExplosionManager/cExplosionCallback.h"
#include "ExplosionManager/eDetonationType.h"

namespace PHYSICS { class cCustomMaterial; }

namespace Equip
{
    class cHWProjectile : public cWeaponProjectile, public ExplosionManager::cExplosionCallback
    {
    public:
        // CD2's qualified base calls in cFlocket reach these HW-projectile
        // implementations, distinct from cWeaponProjectile's replication bodies.
        virtual void ReplicateInitialFields();
        virtual void ReplicateFields();
        // CD2 spawning initializer 0x82FD27B0 names placement factory 0x8262a7e0.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 0x8262A7F8 creates the named runtime descriptor.
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcHWProjectileClass;     // RuffKing's name
        // CD2 0x8262A778; its class-factory registrar (0x82FD2760) names it.
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        cHWProjectile();
        virtual ~cHWProjectile();
        virtual const char *RetClassName() const;      // slot 11
        virtual void NotifyDetonation(cGameBase *, CHARACTER::cCharacterInterface *, unsigned char);
        // Slots 364 to 374 (RuffKing's names and order; the three-argument Launch is declared first because the
        // compiler gives overloads their slots in reverse).
        virtual void EventCollision(PHYSICS::cBody *pBody, const PHYSICS::cCustomMaterial &material,
                                    const Fun_Runtime::Vec3 &vHitPos, const Fun_Runtime::Vec3 &vHitNormal);   // 364
        virtual void Launch(float fInitProjectileVel, const Fun_Runtime::Vec3 &vecTargetPoint, float fAccuracy);   // 366
        virtual void Launch(float fInitProjectileVel, const Fun_Runtime::Vec3 &vecTargetDir);                      // 365
        virtual void SetExplosiveSkillLevel(unsigned char nLevel);   // 367
        virtual float RetDamageRadius() const;                       // 368
        virtual void UpdateExplosionTimer(float dT);                 // 369
        virtual void InitiateExplosion(ExplosionManager::eDetonationType eDT, unsigned short nMaterialID,
                                       const Fun_Runtime::Mtx &mExp, const Fun_Runtime::Vec3 &vDecalPos);    // 370
        virtual int SetupCollisionFilter();                          // 371
        virtual void SpawnEffect();                                  // 372
        virtual void UpdateAttachedEffect();                         // 373
        virtual void ReleaseEffect();                                // 374

    private:
        unsigned char m_unmodelled874[0x970 - 0x874];

        // CD2: cHWProjectile's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual Fun_Runtime::RetVal Term(); // 6: 0x8262AE08
        virtual bool EnterPhysicalState(); // 7: 0x8262C690
        virtual Fun_Runtime::RetVal Init(GOM::cSpawner const *); // 18: 0x8262AD90
        virtual void Slot23(); // 23: 0x82625800
        virtual void Slot24(); // 24: 0x8262BB08
        virtual void Slot27(); // 27: 0x82580578
        virtual bool EnterRenderableState(eResourcesType); // 31: 0x82625738
        virtual void LeaveRenderableState(); // 32: 0x82580578
        virtual void vf76(); // 76: 0x8262CA98
        virtual void vf166(); // 166: 0x827E56A8
        virtual void vf239(); // 239: 0x827E56A8
        virtual void vf276(); // 276: 0x8262D380
        virtual void vf277(); // 277: 0x8262D400
        virtual void vf300(); // 300: 0x827E56A8
        virtual void vf306(); // 306: 0x8262C2D8
        virtual void vf307(); // 307: 0x8262C228
        virtual void SetStatus(Equip::cEquipment::EQUIP_STATUS); // 316: 0x8262AEB0
        virtual bool CanReleaseNetOwnershipOnAVExit() const; // 348: 0x827E56A8
        virtual int RetNetworkLOD(CHARACTER::cCharacter *,int); // 350: 0x8262AEE8
        virtual Fun_Runtime::Vec3 RetReplicationVelocity(); // 351: 0x8262C138
        virtual unsigned int GetMaxReplicatedFields() const; // cReplicatedClass 23: 0x82889810
    private:
        CD2_LAYOUT_CHECKS(cHWProjectile, CD2_SIZE(cHWProjectile, 0x970))
    };

    // ---- prototype side ----
    // Stand-in for cHWProjectilePrototype (CD2 0x320 bytes): a GOM::cObjectPrototype (its constructor chain reaches
    // 0x82654118) with out-of-line constructor, destructor and HandleAttributes.
    class cHWProjectilePrototype : public cWeaponProjectile::cWeaponProjectilePrototype
    {
    public:
        cHWProjectilePrototype(const RWS::CAttributePacket &);
        virtual ~cHWProjectilePrototype();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        unsigned char m_pad[0x320 - 0x2F0];
        // CD2: cHWProjectilePrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual unsigned int RetPvPKillPoints() const; // 22: 0x826253E0
        virtual unsigned int RetHeadShotKillPoints() const; // 23: 0x826253E0
        virtual unsigned int RetArmKillPoints() const; // 24: 0x826253E0
        virtual unsigned int RetLegKillPoints() const; // 25: 0x826253E0
    };

    class cFlocket : public cHWProjectile
    {
    public:
        Fun_Runtime::Vec3 m_vecTargetPos;     // 0x970
        float m_fFlightTime;                  // 0x980
        Fun_Runtime::Vec3 m_vMovementHint;    // 0x990
        float m_fVertAcc;                     // 0x9A0
        float m_fHorizAcc;                    // 0x9A4
        void *m_pFlockLight;                  // 0x9A8 (VFX::cGlobalLight *)

        static const Fun_Runtime::cClass *ms_pcFlocketClass;
        static const char *const pcFlocketClassID;

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        virtual void UpdateAttachedEffect();
        virtual void ReleaseEffect();
        virtual void ReplicateInitialFields();
        virtual void ReplicateFields();
        void UpdateFlocketLight();
        void DestroyFlocketLight();

        cFlocket();
        virtual ~cFlocket();

        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);

        CD2_LAYOUT_CHECKS(cFlocket,
            CD2_SIZE(cFlocket, 0x9B0)
            CD2_OFFSET(cFlocket, m_vecTargetPos, 0x970)
            CD2_OFFSET(cFlocket, m_fFlightTime, 0x980)
            CD2_OFFSET(cFlocket, m_vMovementHint, 0x990)
            CD2_OFFSET(cFlocket, m_fVertAcc, 0x9A0)
            CD2_OFFSET(cFlocket, m_pFlockLight, 0x9A8))
    };

    class cFlocketPrototype : public cHWProjectilePrototype
    {
    public:
        // CD2 0x82627090: attribute-handler vtable slot 5, returning Ret_OK.
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        char m_nLightID;                  // 0x320
        float m_fLightScaleSml;           // 0x324
        float m_fLightScaleLge;           // 0x328
        float m_fLightZOffset;            // 0x32C
        float m_fLaunchOffset;            // 0x330
        float m_fVertAccMin;              // 0x334
        float m_fVertAccMax;              // 0x338
        float m_fHorizAccMin;             // 0x33C
        float m_fHorizAccMax;             // 0x340
        float m_fFlockTime;               // 0x344
        float m_fOscilFalloffTimeRecip;   // 0x348
        float m_fToTargetAcc;             // 0x34C
        float m_fVertDec;                 // 0x350
        float m_fAirDec;                  // 0x354
        float m_fHorizOscil;              // 0x358
        unsigned int m_pad35C;            // size rounded to 0x360

        cFlocketPrototype(const RWS::CAttributePacket &);
        virtual ~cFlocketPrototype() {}
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);

        CD2_LAYOUT_CHECKS(cFlocketPrototype,
            CD2_SIZE(cFlocketPrototype, 0x360)
            CD2_OFFSET(cFlocketPrototype, m_nLightID, 0x320)
            CD2_OFFSET(cFlocketPrototype, m_fLightScaleSml, 0x324)
            CD2_OFFSET(cFlocketPrototype, m_fHorizOscil, 0x358))
    };
}

#endif // EQUIP_CFLOCKET_H



