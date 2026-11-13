// Script registrar source ownership: CD2 initializer 0x82F85AC8 names cInterestingObject,
// and cleanup 0x8303AE58 destroys the same descriptor. Shared interface names are ours.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "unknown/cInterestingObject.h"
#include "fun_runtime/script_type_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "cd2/memory.h"
#include "unknown/cNotifyPriorityScriptRegistration.h"
#include "unknown/cBasicReactionsScriptRegistration.h"
#include "lua/lua.h"

namespace unknown
{
    static Fun_Runtime::cScriptTypeRegistrar<cInterestingObject> cInterestingObjectScriptRegistrar(
        "cInterestingObject", "cScriptHost");

    unsigned char cInterestingObject::RetBasicReaction()
    {
        return m_eBasicReaction;
    }

    float cInterestingObject::RetMaximumDuration()
    {
        return m_fMaximumDuration;
    }

    float cInterestingObject::RetMinimumDuration()
    {
        return m_fMinimumDuration;
    }

    bool cInterestingObject::IsDangerous()
    {
        return m_bDangerous;
    }

    void cInterestingObject::SetType(int nType)
    {
        m_nType = nType;
    }

    void cInterestingObject::SetMaxReactingChars(unsigned short nMax)
    {
        m_nMaxReactingChars = nMax;
    }

    void cInterestingObject::IncrementReactingCharCount()
    {
        ++m_nReactingCharCount;
    }

    void cInterestingObject::DecrementReactingCharCount()
    {
        --m_nReactingCharCount;
    }

    void cInterestingObject::SetBasicReaction(unsigned char eReaction)
    {
        m_eBasicReaction = eReaction;
    }

    void cInterestingObject::SetMaximumDuration(float fDuration)
    {
        m_fMaximumDuration = fDuration;
    }

    void cInterestingObject::SetMinimumDuration(float fDuration)
    {
        m_fMinimumDuration = fDuration;
    }

    void cInterestingObject::SetPriority(unsigned char ePriority)
    {
        m_ePriority = ePriority;
    }

    void cInterestingObject::SetDangerous(bool bDangerous)
    {
        m_bDangerous = bDangerous;
    }

    Fun_Runtime::cClass &cInterestingObject::StaticCreateClass()
    {
        static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x3EA, "cInterestingObject", 0x40);
        return *descriptor;
    }

    const Fun_Runtime::cClass *cInterestingObject::ms_pcInterestingObjectClass = &cInterestingObject::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cInterestingObjectcScriptHostInheritRegistrar(
        cInterestingObject::StaticCreateClass(), Fun_Runtime::cScriptHost::StaticCreateClass());

    const char *cNotifyPriorityScriptRegistration::RetName() const
    {
        return "eNotifyPriority";
    }

    void cNotifyPriorityScriptRegistration::RegisterValues(lua_State *state)
    {
        lua_pushliteral(state, "eNP_Lowest");
        lua_pushnumber(state, 0.0f);
        lua_settable(state, -3);
        lua_pushliteral(state, "eNP_Low");
        lua_pushnumber(state, 1.0f);
        lua_settable(state, -3);
        lua_pushliteral(state, "eNP_Normal");
        lua_pushnumber(state, 2.0f);
        lua_settable(state, -3);
        lua_pushliteral(state, "eNP_AboveNormal");
        lua_pushnumber(state, 3.0f);
        lua_settable(state, -3);
        lua_pushliteral(state, "eNP_High");
        lua_pushnumber(state, 4.0f);
        lua_settable(state, -3);
        lua_pushliteral(state, "eNP_Critical");
        lua_pushnumber(state, 5.0f);
        lua_settable(state, -3);
    }

    // CD2 0x82F85A38 registers this four-byte enum object at 0x8381C034.
    static cNotifyPriorityScriptRegistration g_cNotifyPriorityScriptRegistration;

    const char *cBasicReactionsScriptRegistration::RetName() const
    {
        return "eBasicReactions";
    }

    void cBasicReactionsScriptRegistration::RegisterValues(lua_State *state)
    {
        lua_pushliteral(state, "eReact_None");
        lua_pushnumber(state, 0.0f);
        lua_settable(state, -3);
        lua_pushliteral(state, "eReact_HeadLookAt");
        lua_pushnumber(state, 1.0f);
        lua_settable(state, -3);
        lua_pushliteral(state, "eReact_HeadOrUpperBodyLookAt");
        lua_pushnumber(state, 2.0f);
        lua_settable(state, -3);
        lua_pushliteral(state, "eReact_UpperBodyLookAt");
        lua_pushnumber(state, 3.0f);
        lua_settable(state, -3);
    }

    // CD2 0x82F85A80 registers this four-byte enum object at 0x8381C038.
    static cBasicReactionsScriptRegistration g_cBasicReactionsScriptRegistration;
}
