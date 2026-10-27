// VFX/cAmbientVFXSpawner.cpp: ambient VFX spawner and prototype classes of Crackdown 2.
// All 21 mapped functions are exact; the three CalcRand functions require LTCG. See config/matched_functions.json.
// HandleAttributes uses GUID assignment before lookup to preserve the target's three GUID temporaries.
#include "VFX/cAmbientVFXSpawner.h"
#include "editor/guid_event_handler.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "rw/rwmem.h"

namespace VFX
{
    const char *const cAmbientVFXPrototypeBase::pcAmbientVFXPrototypeBaseClassID = "cAmbientVFXPrototypeBase";
    const char *const cAmbientVFXPrototype::pcAmbientVFXPrototypeClassID = "cAmbientVFXPrototype";
    const char *const cAmbientVFXSpawner::pcAmbientVFXSpawnerClassID = "cAmbientVFXSpawner";

    const char *cAmbientVFXPrototypeBase::RetClassName() const
    {
        return pcAmbientVFXPrototypeBaseClassID;
    }

    const char *cAmbientVFXPrototype::RetClassName() const
    {
        return pcAmbientVFXPrototypeClassID;
    }

    RWS::CAttributeHandler *cAmbientVFXPrototype::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cAmbientVFXPrototype(packet);
    }

    Fun_Runtime::cClass &cAmbientVFXSpawner::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAmbientVFXSpawner_Class =
            new Fun_Runtime::cClass(0x5086C, "cAmbientVFXSpawner", 0x50);
        return *cAmbientVFXSpawner_Class;
    }

    const Fun_Runtime::cClass &cAmbientVFXSpawner::RetClass() const
    {
        return *ms_pcAmbientVFXSpawnerClass;
    }

    bool cAmbientVFXSpawner::IsA(const Fun_Runtime::cClass &test) const
    {
        return ms_pcAmbientVFXSpawnerClass->IsA(test);
    }

    void cAmbientVFXSpawner::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        for (RWS::CAttributeCommandIterator it(packet, pcAmbientVFXSpawnerClassID); !it.IsFinished(); ++it)
        {
            if (it->GetCommandId() == 0)
            {
                RWS::RWSGUID guid;
                guid = it->GetAs_RWSGUID();
                m_pPrototype = Editor::cGUIDLinker<cAmbientVFXPrototype>::LinkToObject(guid);
            }
        }
        if (m_pPrototype)
        {
            cAmbientVFXSpawnerBase::HandleAttributes(packet);
            if (packet.IsInstanceCreationPacket())
                cAmbientVFXManager::RetInstancePtr()->RegisterAmbientVFXSpawner(this);
        }
    }

    RWS::CAttributeHandler *cAmbientVFXSpawner::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        cAmbientVFXSpawner *p = new cAmbientVFXSpawner(packet);
        p->HandleAttributes(packet);
        return 0;
    }

    void cAmbientVFXSpawner::OnBecomeRelevantToPlayer()
    {
        if (!RetAmbientVFXPrototype()->m_bRandSpawn)
            return;
        CalcRandInitSpawnTime();
    }

    void cAmbientVFXSpawner::OnBecomeIrrelevantToPlayer()
    {
        m_nRespawnTime = 0xFFFFFFFF;
        m_nExpireTime = 0xFFFFFFFF;
    }

    void cAmbientVFXSpawner::CalcRandInitSpawnTime()
    {
        cAmbientVFXPrototype *proto = RetAmbientVFXPrototype();
        float r = (float)ms_RandGen.Rand();
        float f = r * (proto->m_fInitSpawnTimeMax - proto->m_fInitSpawnTimeMin) * 0.000030518509f + proto->m_fInitSpawnTimeMin;
        m_nRespawnTime = RWS::Time::RetGameTime() - (unsigned int)(f * -1000.0f);
    }

    void cAmbientVFXSpawner::CalcRandRespawnTime()
    {
        cAmbientVFXPrototype *proto = RetAmbientVFXPrototype();
        float r = (float)ms_RandGen.Rand();
        float f = r * (proto->m_fRandRespawnTimeMax - proto->m_fRandRespawnTimeMin) * 0.000030518509f + proto->m_fRandRespawnTimeMin;
        m_nRespawnTime = RWS::Time::RetGameTime() - (unsigned int)(f * -1000.0f);
    }

    void cAmbientVFXSpawner::CalcRandLifetime()
    {
        cAmbientVFXPrototype *proto = RetAmbientVFXPrototype();
        float r = (float)ms_RandGen.Rand();
        float f = r * (proto->m_fRandLifetimeMax - proto->m_fRandLifetimeMin) * 0.000030518509f + proto->m_fRandLifetimeMin;
        m_nExpireTime = RWS::Time::RetGameTime() - (unsigned int)(f * -1000.0f);
    }

    bool cAmbientVFXSpawner::IsVFXFinished() const
    {
        if (RWS::Time::RetGameTime() > m_nExpireTime)
            return true;
        return cAmbientVFXSpawnerBase::IsVFXFinished();
    }

    void cAmbientVFXSpawner::OnVFXFinished()
    {
        cAmbientVFXSpawnerBase::OnVFXFinished();
        if (RetAmbientVFXPrototype()->m_bRandSpawn)
            CalcRandRespawnTime();
    }

    bool cAmbientVFXSpawner::CanSpawn() const
    {
        float phase = Sim::cTimeOfDay::ms_pInstance->m_fPhase;
        cAmbientVFXPrototype *proto = RetAmbientVFXPrototype();
        float start = proto->m_fToDStart;
        float end = proto->m_fToDEnd;
        if (start != end)
        {
            if (start < end)
            {
                if (phase < start || phase > end)
                    return false;
            }
            else if (phase > end && phase < start)
            {
                return false;
            }
        }
        if (proto->m_bRandSpawn && m_nRespawnTime > RWS::Time::RetGameTime())
            return false;
        return cAmbientVFXSpawnerBase::CanSpawn();
    }

    bool cAmbientVFXSpawner::ReleaseVFX()
    {
        if (cAmbientVFXSpawnerBase::ReleaseVFX())
        {
            if (RetAmbientVFXPrototype()->m_bRandSpawn)
                CalcRandRespawnTime();
            return true;
        }
        return false;
    }

    static RWS::CClassFactory::CRegistrar cAmbientVFXSpawnerRegistrar(
        "cAmbientVFXSpawner", cAmbientVFXSpawner::MakeNew, 0x50, false);

    // Defined in this file: RuffKing's cAmbientVFXSpawner.obj holds its dynamic initializer and at-exit destructor.
    Fun_Runtime::cRandGen cAmbientVFXSpawnerBase::ms_RandGen;

}
