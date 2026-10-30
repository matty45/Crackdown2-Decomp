// VFX::cAmbientVFXSpawner and VFX::cAmbientVFXPrototype(Base): ambient VFX spawn points placed in the editor.
// CD2 layouts (worked out from F05/F07/F11/F12/F15-F22):
//   cAmbientVFXPrototypeBase : CAttributeHandler            size 0x30  (fields 0x18..0x2E)
//   cAmbientVFXPrototype     : cAmbientVFXPrototypeBase     size 0x68  (GUID event handler at 0x30, fields 0x44..0x65)
//   cAmbientVFXSpawnerBase   (vptr + 12 unknown bytes, then rot/pos/instance/proto)   size 0x40
//   cAmbientVFXSpawner       : cAmbientVFXSpawnerBase       size 0x50  (expire/respawn time at 0x40/0x44, 16-byte aligned)
// The 12 bytes after the vptr of cAmbientVFXSpawnerBase are not initialised by any CD2 constructor, so they are
// just padding here. cAmbientVFXSpawnerBase is a stand-in with the right virtual slots (RetClass, IsA, dtor, CanSpawn,
// OnVFXFinished, OnBecomeRelevantToPlayer, OnBecomeIrrelevantToPlayer, IsVFXFinished, SpawnVFX, ReleaseVFX);
// its trivial members are inline because CD2 inlines them (IsVFXFinished, CanSpawn, OnVFXFinished).
#ifndef VFX_CAMBIENTVFXSPAWNER_H
#define VFX_CAMBIENTVFXSPAWNER_H

#include "rws/attributes.h"
#include "editor/guid_event_handler.h"
#include "cd2/layout.h"
#include "fun_runtime/class.h"
#include "fun_runtime/randgen.h"
#include "fun_runtime/vec3.h"
#include "Sim/cTimeOfDay.h"

namespace Fun_Runtime
{
    // Stand-ins: RuffKing names, layouts as used here.
    __declspec(align(16)) struct Quat { float v[4]; };
}

namespace RWS
{
    namespace Time
    {
        // Game time in milliseconds; CD2 inlines the "frozen/replay time" test. Names are ours.
        extern unsigned char g_bUseStoredTime;
        extern unsigned int g_nStoredTime;
        unsigned int CalcGameTime();
        inline unsigned int RetGameTime() { return g_bUseStoredTime ? g_nStoredTime : CalcGameTime(); }
    }
}

namespace VFX
{
    class cParticleEffectInstance
    {
    public:
        unsigned char m_pad[0x74];
        unsigned int m_Flags;  // bit 12: finished
    };

    class cAmbientVFXPrototypeBase : public RWS::CAttributeHandler
    {
    public:
        float m_fSpawnDistanceMinSq;
        float m_fSpawnDistanceMaxSq;
        float m_fScaleOverride;
        float m_fFadeOutTime;
        int m_nEffectID;
        unsigned char m_nDefaultPriority;
        bool m_bOnFire;
        unsigned char m_nFadeMode;

        static const char *const pcAmbientVFXPrototypeBaseClassID;

        virtual const char *RetClassName() const;
        virtual void Destruct();
        __forceinline cAmbientVFXPrototypeBase(const RWS::CAttributePacket &)
            : m_fSpawnDistanceMinSq(0.0f), m_fSpawnDistanceMaxSq(0.0f), m_fScaleOverride(1.0f), m_fFadeOutTime(0.0f),
              m_nEffectID(-1), m_nDefaultPriority(0), m_bOnFire(false), m_nFadeMode(0) {}
        virtual ~cAmbientVFXPrototypeBase() {}
        virtual void HandleAttributes(const RWS::CAttributePacket &);

        CD2_LAYOUT_CHECKS(cAmbientVFXPrototypeBase,
            CD2_SIZE(cAmbientVFXPrototypeBase, 0x30)
            CD2_OFFSET(cAmbientVFXPrototypeBase, m_fSpawnDistanceMinSq, 0x18)
            CD2_OFFSET(cAmbientVFXPrototypeBase, m_nEffectID, 0x28)
            CD2_OFFSET(cAmbientVFXPrototypeBase, m_nFadeMode, 0x2E))
    };

    class cAmbientVFXPrototype : public cAmbientVFXPrototypeBase
    {
    public:
        Editor::cGUIDEventHandler<cAmbientVFXPrototype> m_EventHandler;
        float m_fInitSpawnTimeMin;
        float m_fInitSpawnTimeMax;
        float m_fRandRespawnTimeMin;
        float m_fRandRespawnTimeMax;
        float m_fRandLifetimeMin;
        float m_fRandLifetimeMax;
        float m_fToDStart;
        float m_fToDEnd;
        bool m_bIsExplosion;
        bool m_bRandSpawn;

        static const char *const pcAmbientVFXPrototypeClassID;

        virtual const char *RetClassName() const;
        __forceinline cAmbientVFXPrototype(const RWS::CAttributePacket &packet)
            : cAmbientVFXPrototypeBase(packet)
        {
            m_bIsExplosion = false;
            m_bRandSpawn = false;
            m_fInitSpawnTimeMin = 0.0f;
            m_fInitSpawnTimeMax = 0.0f;
            m_fRandRespawnTimeMin = 0.0f;
            m_fRandRespawnTimeMax = 0.0f;
            m_fRandLifetimeMin = 0.0f;
            m_fRandLifetimeMax = 0.0f;
            m_fToDStart = 0.0f;
            m_fToDEnd = 0.0f;
        }
        virtual ~cAmbientVFXPrototype() {}

        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);

        CD2_LAYOUT_CHECKS(cAmbientVFXPrototype,
            CD2_SIZE(cAmbientVFXPrototype, 0x68)
            CD2_OFFSET(cAmbientVFXPrototype, m_EventHandler, 0x30)
            CD2_OFFSET(cAmbientVFXPrototype, m_fInitSpawnTimeMin, 0x44)
            CD2_OFFSET(cAmbientVFXPrototype, m_fToDStart, 0x5C)
            CD2_OFFSET(cAmbientVFXPrototype, m_bRandSpawn, 0x65))
    };

    class cAmbientVFXSpawnerBase
    {
    public:
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual ~cAmbientVFXSpawnerBase();

        cAmbientVFXSpawnerBase(const RWS::CAttributePacket &)
            : m_pVFXInstance(0), m_pNextActiveSpatialVFX(0), m_pPrototype(0), m_bInSpatialGrid(false),
              m_bRelevantToPlayer(false) {}

        void HandleAttributes(const RWS::CAttributePacket &);

    protected:
        virtual bool CanSpawn() const { return m_bRelevantToPlayer != 0; }
        virtual void OnVFXFinished() { ReleaseVFX(); }
        virtual void OnBecomeRelevantToPlayer();
        virtual void OnBecomeIrrelevantToPlayer();
        virtual bool IsVFXFinished() const
        {
            // The finished bit goes through a bool local: that is what makes CD2 extract it (extrwi) instead of
            // testing it in place (rlwinm mask).
            unsigned int flags = m_pVFXInstance->m_Flags;
            bool bFinishedBit = ((flags >> 12) & 1) != 0;
            unsigned char bFinished = bFinishedBit || (flags & 0x400B) == 0;
            return bFinished != 0;
        }
        virtual bool SpawnVFX();
        virtual bool ReleaseVFX();

        Fun_Runtime::Quat m_Rot;
        Fun_Runtime::Vec3 m_Pos;
        cParticleEffectInstance *m_pVFXInstance;
        cAmbientVFXSpawnerBase *m_pNextActiveSpatialVFX;
        cAmbientVFXPrototypeBase *m_pPrototype;
        unsigned char m_bInSpatialGrid;
        unsigned char m_bRelevantToPlayer;
        static Fun_Runtime::cRandGen ms_RandGen;
    };

    class cAmbientVFXManager
    {
    public:
        static cAmbientVFXManager *ms_pInstance;
        static cAmbientVFXManager *RetInstancePtr() { return ms_pInstance; }
        void RegisterAmbientVFXSpawner(cAmbientVFXSpawnerBase *);
    };

    class cAmbientVFXSpawner : public cAmbientVFXSpawnerBase
    {
    protected:
        unsigned int m_nExpireTime;
        unsigned int m_nRespawnTime;

    public:
        static const Fun_Runtime::cClass *ms_pcAmbientVFXSpawnerClass;
        static const char *const pcAmbientVFXSpawnerClassID;

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        cAmbientVFXSpawner(const RWS::CAttributePacket &packet)
            : cAmbientVFXSpawnerBase(packet), m_nExpireTime(0xFFFFFFFF), m_nRespawnTime(0xFFFFFFFF) {}
        void HandleAttributes(const RWS::CAttributePacket &);
        cAmbientVFXPrototype *RetAmbientVFXPrototype() const { return (cAmbientVFXPrototype *)m_pPrototype; }

    protected:
        virtual bool CanSpawn() const;
        virtual void OnVFXFinished();
        virtual void OnBecomeRelevantToPlayer();
        virtual void OnBecomeIrrelevantToPlayer();
        virtual bool IsVFXFinished() const;
        virtual bool SpawnVFX();
        virtual bool ReleaseVFX();
        void CalcRandInitSpawnTime();
        void CalcRandRespawnTime();
        void CalcRandLifetime();

    public:
        virtual ~cAmbientVFXSpawner();

        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);

        CD2_LAYOUT_CHECKS(cAmbientVFXSpawner,
            CD2_SIZE(cAmbientVFXSpawner, 0x50)
            CD2_OFFSET(cAmbientVFXSpawner, m_pPrototype, 0x38)
            CD2_OFFSET(cAmbientVFXSpawner, m_bRelevantToPlayer, 0x3D)
            CD2_OFFSET(cAmbientVFXSpawner, m_nExpireTime, 0x40)
            CD2_OFFSET(cAmbientVFXSpawner, m_nRespawnTime, 0x44))
    };
}

#endif // VFX_CAMBIENTVFXSPAWNER_H
