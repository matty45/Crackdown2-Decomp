// Equip/cFlocket.cpp: cFlocket of Crackdown 2.
// Measurement batch 2 (2026-10-23, Sonnet 5.5): 28 functions byte-exact, 0 tracked as work in progress
// (config/matched_functions.json). Unknown bases and callees are stand-ins named in the header; out-of-line
// callees without a known name are declared as Ext_<address>.
// Equip/cFlocket.cpp: the Flocket (homing swarm) projectile and its attribute prototype, Crackdown 2.
// Measurement batch 2 (gameplay logic). See cFlocket.h for the layout and the stand-in bases.
#include <new>
#include "Equip/cFlocket.h"
#include "rw/rwmem.h"

namespace VFX
{
    class cGlobalLight;
    class cGlobalLightPool;
    extern cGlobalLightPool g_GlobalLightPool;
    void RemoveGlobalLight(cGlobalLight *);                 // sub_827FC650
    void ReturnLight(cGlobalLightPool *, cGlobalLight *);   // sub_825FF700
}

namespace Equip { class cRegClassC; }
namespace Net
{
    // Replication packet builder/reader (sub_8282B698 / B588 / C160 / C0D0); names are ours.
    class cFieldWriter;
    cFieldWriter *BeginVec3(int id, int bits, __vector4 v);
    cFieldWriter *AddFloat(cFieldWriter *w, int id, int flags, float f);
}

// CAttributeCommand::GetAs_char_ptr is inline in CD2 (address of the data word).
inline const char *RWS::CAttributeCommand::GetAs_char_ptr() const { return (const char *)&chunk_.data_; }

namespace Equip
{
    // Resolves a light name to its table index (sub_827FBF30 in CD2); name is ours.
    char LookupLightID(const char *name);

    const char *const cFlocket::pcFlocketClassID = "cFlocket";

    const Fun_Runtime::cClass &cFlocket::RetClass() const
    {
        return *ms_pcFlocketClass;
    }

    bool cFlocket::IsA(const Fun_Runtime::cClass &test) const
    {
        return ms_pcFlocketClass->IsA(test);
    }

    const char *cFlocket::RetClassName() const
    {
        return pcFlocketClassID;
    }

    RWS::CAttributeHandler *cFlocketPrototype::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cFlocketPrototype(packet);
    }

    RWS::CAttributeHandler *cFlocket::SpawnFromPrototype(GOM::cObjectPrototype *, void *pMem)
    {
        if (pMem)
            return new (pMem) cFlocket();
        return 0;
    }

    Fun_Runtime::cClass &cFlocket::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cFlocket_Class = new Fun_Runtime::cClass(0x605E, "cFlocket", 0x9B0);
        return *cFlocket_Class;
    }

    cFlocket::cFlocket() : m_fFlightTime(0.0f)
    {
        m_pFlockLight = 0;
        m_fVertAcc = 0.0f;
        m_fHorizAcc = 0.0f;
    }

    cFlocket::~cFlocket()
    {
    }

    cFlocketPrototype::cFlocketPrototype(const RWS::CAttributePacket &packet)
        : cHWProjectilePrototype(packet)
    {
        m_nLightID = -1;
        m_fLightScaleSml = 0.5f;
        m_fLightScaleLge = 3.0f;
        m_fLightZOffset = -0.4f;
        m_fLaunchOffset = 0.05f;
        m_fVertAccMin = 20.0f;
        m_fVertAccMax = 50.0f;
        m_fHorizAccMin = -50.0f;
        m_fHorizAccMax = 50.0f;
        m_fFlockTime = 0.3f;
        m_fOscilFalloffTimeRecip = 1.0f / 6.0f;
        m_fToTargetAcc = 100.0f;
        m_fVertDec = 1.0f;
        m_fAirDec = 3.0f;
        m_fHorizOscil = 0.25f;
    }

    void cFlocketPrototype::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cHWProjectilePrototype::HandleAttributes(packet);
        for (RWS::CAttributeCommandIterator it(packet, cFlocket::pcFlocketClassID); !it.IsFinished(); ++it)
        {
            switch (it->GetCommandId())
            {
            case 0:
                m_nLightID = LookupLightID(it->GetAs_char_ptr());
                break;
            case 1:
                { float mem = it->GetAs_float(); RwMemNative32(&mem, 4); m_fLightScaleSml = mem; }
                break;
            case 2:
                { float mem = it->GetAs_float(); RwMemNative32(&mem, 4); m_fLightScaleLge = mem; }
                break;
            }
        }
    }


    inline void cFlocket::DestroyFlocketLight()
    {
        if (m_pFlockLight)
        {
            VFX::RemoveGlobalLight((VFX::cGlobalLight *)m_pFlockLight);
            VFX::ReturnLight(&VFX::g_GlobalLightPool, (VFX::cGlobalLight *)m_pFlockLight);
            m_pFlockLight = 0;
        }
    }

    void cFlocket::UpdateAttachedEffect()
    {
        cHWProjectile::UpdateAttachedEffect();
        if (m_pFlockLight)
            UpdateFlocketLight();
    }

    void cFlocket::ReleaseEffect()
    {
        cHWProjectile::ReleaseEffect();
        DestroyFlocketLight();
    }

    void cFlocket::ReplicateInitialFields()
    {
        cHWProjectile::ReplicateInitialFields();
        Net::cFieldWriter *w = Net::BeginVec3(24, 96, Fun_Runtime::Vec3(m_vMovementHint).v);
        w = Net::AddFloat(w, 25, 1, m_fVertAcc);
        Net::AddFloat(w, 26, 1, m_fHorizAcc);
    }

    void cFlocket::ReplicateFields()
    {
        cHWProjectile::ReplicateFields();
        Fun_Runtime::Vec3 *pHint = &m_vMovementHint;
        Fun_Runtime::Vec3 v = *pHint;
        ReadVec3(&v, 24);
        ReadFloat(&m_fVertAcc, 25);
        ReadFloat(&m_fHorizAcc, 26);
        if (m_nUnk88 == 199)
        {
            pHint->x = v.x;
            pHint->y = v.y;
            pHint->z = v.z;
        }
    }
    static RWS::CClassFactory::CRegistrar cFlocketRegistrar(
        "cFlocket", cFlocketPrototype::MakeNew, 0x9B0, false);
}

