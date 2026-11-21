// src/cCwTransCharacter.cpp
//
// Class: CHARACTER::cCwTransCharacter. Accessors and registration are reconstructed below.
// The address range and ownership evidence are in config/splits.txt; the class is not in RuffKing.
//
// Burn's cPlayerCharacter supplies names for the shared skill and replication behaviour; CD2 supplies the layout.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cCwTransCharacter.cpp

// Byte 0x2DA6 and its two virtual accessors remain unnamed. Other matched overrides use cCharacter's recovered slots.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "CHARACTER/cCharacter.h"
#include "CHARACTER/cCwTransCharacter.h"
#include "rws/classfactory.h"
#include "rws/eventid.h"
#include "rws/msg.h"
#include "fun_runtime/retval.h"
#include "cd2/memory.h"
#include <new>

namespace CHARACTER
{
    const Fun_Runtime::cClass &cCwTransCharacter::RetClass() const
    {
        return *ms_pcCwTransCharacterClass;
    }

    bool cCwTransCharacter::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcCwTransCharacterClass->IsA(c);
    }

    RWS::CAttributeHandler *cCwTransCharacter::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cCwTransCharacterPrototype(packet);
    }

    RWS::CAttributeHandler *cCwTransCharacter::SpawnFromPrototype(GOM::cObjectPrototype *prototype, void *memory)
    {
        if (memory)
            return new (memory) cCwTransCharacter(prototype);
        return 0;
    }

    static RWS::CClassFactory::CRegistrar cCwTransCharacterRegistrar(
        "cCwTransCharacter", cCwTransCharacter::MakeNew, 0x2E00, false);

    const char *cCwTransCharacter::RetClassName() const
    {
        return "cCwTransCharacter";
    }

    bool cCwTransCharacter::IsTransformationRequired() const
    {
        return m_SkillSet.IsTransformRequired();
    }

    unsigned char cCwTransCharacter::RetAthleticLevel() const
    {
        return RetSkill(RPG::eSk_Athletics);
    }

    unsigned char cCwTransCharacter::RetExplosivesLevel() const
    {
        return RetSkill(RPG::eSk_Explosives);
    }

    unsigned char cCwTransCharacter::RetStrengthLevel() const
    {
        return RetSkill(RPG::eSk_Fighting);
    }

    unsigned char cCwTransCharacter::RetFirearmsLevel() const
    {
        return RetSkill(RPG::eSk_FireArms);
    }

    bool cCwTransCharacter::IsSkillAndBonusMaxed(unsigned int skill) const
    {
        return m_SkillSet.IsSkillAndBonusMaxed(skill);
    }

    bool cCwTransCharacter::IsSkillMaxed(unsigned int skill) const
    {
        return m_SkillSet.IsSkillMaxed(skill);
    }

    bool cCwTransCharacter::vf384(unsigned int skill) const
    {
        return m_SkillSet.IsSkillAtLevelSix(skill);
    }

    bool cCwTransCharacter::IsPowerUpActive(ePowerUp powerUp)
    {
        return (m_nPowerUpStatus & (1 << powerUp)) != 0;
    }

    unsigned int cCwTransCharacter::GetMaxReplicatedFields() const
    {
        return 88;
    }

    bool cCwTransCharacter::IsInDeathLimbo() const
    {
        return m_bInDeathLimbo;
    }

    unsigned char cCwTransCharacter::vf406() const
    {
        return m_byte2DA6;
    }

    void cCwTransCharacter::vf407(unsigned char value)
    {
        m_byte2DA6 = value;
    }

    void cCwTransCharacter::SetKilledByFriendly(bool friendly)
    {
        m_bKilledByFriendly = friendly;
    }

    unsigned int cCwTransCharacter::RetLastVehicleHitID() const
    {
        return m_nLastVehicleHitID;
    }

    Fun_Runtime::cClass &cCwTransCharacter::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cCwTransCharacterClass = new Fun_Runtime::cClass(0x6A1, "cCwTransCharacter", 0x2E00);
        return *cCwTransCharacterClass;
    }

    void cCwTransCharacter::TriggerEnterWater(float fWaterLevel)
    {
        cCharacter::TriggerEnterWater(fWaterLevel);
    }

    void cCwTransCharacter::TriggerExitWater(float fWaterLevel)
    {
        cCharacter::TriggerExitWater(fWaterLevel);
    }

    void cCwTransCharacter::TermClump()
    {
        cCharacter::TermClump();
    }

    char cCwTransCharacter::RetActualSkill(unsigned int skill) const
    {
        return m_SkillSet.RetActualSkill(skill);
    }

    Fun_Runtime::RetVal cCwTransCharacter::cCwTransCharacterPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }

    void cCwTransCharacter::cCwTransCharacterPrototype::SetCharacterProfile(unsigned char nLevel, const char *szProfileName)
    {
        RWS::CEventId id;
        RWS::CEventHandler::RegisterMsg(id, szProfileName, "return cCharacterProfile*");
        RWS::CMsg message(id, 0);
        RWS::SendMsg(message);
        m_pProfileArray[nLevel] = static_cast<cCharacterProfile *>(message.pData);
        RWS::CEventHandler::UnRegisterMsg(id);
    }

    void cCwTransCharacter::cCwTransCharacterPrototype::SetExplosivesProfile(unsigned char nLevel, const char *szProfileName)
    {
        RWS::CEventId id;
        RWS::CEventHandler::RegisterMsg(id, szProfileName, "return cExplosivesSkillProfile*");
        RWS::CMsg message(id, 0);
        RWS::SendMsg(message);
        m_pExplosivesArray[nLevel] = static_cast<RPG::cExplosivesSkillProfile *>(message.pData);
        RWS::CEventHandler::UnRegisterMsg(id);
    }

    void cCwTransCharacter::cCwTransCharacterPrototype::SetStrengthProfile(unsigned char nLevel, const char *szProfileName)
    {
        RWS::CEventId id;
        RWS::CEventHandler::RegisterMsg(id, szProfileName, "return cStrengthSkillProfile*");
        RWS::CMsg message(id, 0);
        RWS::SendMsg(message);
        m_pStrengthArray[nLevel] = static_cast<cStrengthSkillProfile *>(message.pData);
        RWS::CEventHandler::UnRegisterMsg(id);
    }

    const Anim::cAnimationProfile *cCwTransCharacter::cCwTransCharacterPrototype::RetAnimationProfile(unsigned char nLevel) const
    {
        return m_pAnimationProfileArray[nLevel];
    }

    const cCharacterProfile *cCwTransCharacter::cCwTransCharacterPrototype::RetPtrProfile(unsigned char nLevel) const
    {
        return m_pProfileArray[nLevel];
    }

    const RPG::cExplosivesSkillProfile *cCwTransCharacter::cCwTransCharacterPrototype::RetPtrExplosives(unsigned char nLevel) const
    {
        return m_pExplosivesArray[nLevel];
    }

    const cStrengthSkillProfile *cCwTransCharacter::cCwTransCharacterPrototype::RetPtrStrength(unsigned char nLevel) const
    {
        return m_pStrengthArray[nLevel];
    }

    unsigned int cCwTransCharacter::cCwTransCharacterPrototype::RetSkeletonID(unsigned char nLevel) const
    {
        return m_eSkeletonTypeIndex[nLevel];
    }

    float cCwTransCharacter::cCwTransCharacterPrototype::RetInitMinScale(unsigned char nLevel) const
    {
        return m_fInitMinScales[nLevel];
    }

    float cCwTransCharacter::cCwTransCharacterPrototype::RetInitMaxScale(unsigned char nLevel) const
    {
        return m_fInitMaxScales[nLevel];
    }

    float cCwTransCharacter::vf132()
    {
        return g_8373BB20;
    }

    void cCwTransCharacter::SetLastVehicleHitID(unsigned int nVehicleID)
    {
        m_nLastVehicleHitID = nVehicleID;
        m_fLastVehicleHitTimer = 0.4f;
    }

    const Fun_Runtime::cClass *cCwTransCharacter::ms_pcCwTransCharacterClass = &cCwTransCharacter::StaticCreateClass();

    // CD2 0x82FABCC8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cCwTransCharactercCharacterInheritRegistrar(
        CHARACTER::cCwTransCharacter::StaticCreateClass(), CHARACTER::cCharacter::StaticCreateClass());

    // CD2 0x82FABD80: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cCwTransCharacterSpawningRegistrar(
        cCwTransCharacter::StaticCreateClass(), cCwTransCharacter::SpawnFromPrototype);
}
