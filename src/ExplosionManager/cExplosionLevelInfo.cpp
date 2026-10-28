// ExplosionManager/cExplosionLevelInfo.cpp: four mapped functions verified exact.
// Reference layout: include/ref/ruffking/ExplosionManager_cExplosionLevelInfo.h.
// The constructor supplies the vtable used by the deleting destructor; its factory
// has not been promoted as an exact match.

#include "ExplosionManager/cExplosionLevelInfo.h"
#include "cd2/memory.h"
#include "rws/classfactory.h"
#include "fun_runtime/class.h"

namespace ExplosionManager
{
    cExplosionLevelInfo::cExplosionLevelInfo(const RWS::CAttributePacket &)
        : m_nLevel(0), m_fExplosionTime(1.0f), m_fVFXScale(1.0f),
          m_fAccumulationRadius(5.0f),
          m_fMaxDamage(Fun_Runtime::g_GlobalConstants.CONST_FLOAT_0),
          m_fMinDamage(Fun_Runtime::g_GlobalConstants.CONST_FLOAT_0),
          m_fMaxForce(Fun_Runtime::g_GlobalConstants.CONST_FLOAT_0),
          m_fDamageRadius(10.0f), m_fDecalRadius(5.0f),
          m_nExplosionEffectLevel(Fun_Runtime::g_GlobalConstants.CONST_INT_0),
          m_fExplosionSoundVolume(Fun_Runtime::g_GlobalConstants.CONST_FLOAT_0),
          m_nWaterExplosionVFXID(-1), m_nUVExplosionVFXID(-1), m_fCameraShakeAmount(20.0f)
    {
    }

    RWS::CAttributeHandler *cExplosionLevelInfo::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cExplosionLevelInfo(packet);
    }

    const char *cExplosionLevelInfo::RetClassName() const
    {
        return "cExplosionLevelInfo";
    }

    static RWS::CClassFactory::CRegistrar cExplosionLevelInfoRegistrar(
        "cExplosionLevelInfo", cExplosionLevelInfo::MakeNew, 0x80, false);
}
