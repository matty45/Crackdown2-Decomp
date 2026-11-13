// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "fun_runtime/retval.h"
#include "CHARACTER/cCwCharacterStateProfile.h"
#include "CHARACTER/cCharacterStatesScriptRegistration.h"
#include "rws/classfactory.h"
#include "rws/msg.h"
#include "lua/lua.h"

namespace CHARACTER
{
    const char *cCwCharacterStateProfile::RetClassName() const
    {
        return "cCwCharacterStateProfile";
    }

    const char *cCharacterStatesScriptRegistration::RetName() const
    {
        return "eCharacterStates";
    }

    void cCharacterStatesScriptRegistration::RegisterValues(lua_State *state)
    {
        lua_pushliteral(state, "nNormal");
        lua_pushnumber(state, 0.0f);
        lua_settable(state, -3);
    }

    cCwCharacterStateProfile::~cCwCharacterStateProfile()
    {
        UnLinkMsg(m_Msg_Return_Self);
        UnRegisterMsg(m_Msg_Return_Self);
    }

    static RWS::CClassFactory::CRegistrar cCwCharacterStateProfileRegistrar(
        "cCwCharacterStateProfile", cCwCharacterStateProfile::MakeNew, 0xCC, false);

    // CD2 initializer 0x82FACB88 registers the enum object and installs table 0x82112CA8.
    static cCharacterStatesScriptRegistration g_cCharacterStatesScriptRegistration;

    Fun_Runtime::RetVal cCwCharacterStateProfile::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }

    void cCwCharacterStateProfile::HandleEvents(RWS::CMsg &msg)
    {
        if (msg.Id == m_Msg_Return_Self)
            msg.pData = this;
    }
}
