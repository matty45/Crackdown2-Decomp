// ExplosionManager/cExplosionLevelInfo.cpp.
// Reference layout: refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/ExplosionManager/cExplosionLevelInfo.h.
// CD2 inlines the constructor in its factory; it supplies the vtable used by the deleting destructor.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
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
