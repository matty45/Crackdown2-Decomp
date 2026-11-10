// src/PHYSICS/cBody.cpp
//
// Class: cBody (namespace: PHYSICS). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cBody.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Physics/cBody.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/PHYSICS/cBody.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "gom/proto_registrar.h"
#include "PHYSICS/cDynamicBody.h"
#include "GDb/cDebugPageHandler.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/game_base.h"
#include "rws/classfactory.h"
#include "PHYSICS/cBody.h"
#include "cd2/memory.h"
#include "fun_runtime/script_type_registrar.h"

namespace PHYSICS
{
    const Fun_Runtime::cClass *cBody::ms_pcBodyClass = &cBody::StaticCreateClass();

    Fun_Runtime::cClass &cBody::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cBodyClass = new Fun_Runtime::cClass(0x63C, "cBody", 0x250);
        return *cBodyClass;
    }

    static RWS::CClassFactory::CRegistrar cBodyRegistrar(
        "cBody", cBody::MakeNew, 0x250, false);

    // CD2 0x82FDF610: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cBodycGameBaseInheritRegistrar(
        PHYSICS::cBody::StaticCreateClass(), cGameBase::StaticCreateClass());

    // CD2 0x82FDF678: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cBodycDebugPageHandlerInheritRegistrar(
        PHYSICS::cBody::StaticCreateClass(), GDb::cDebugPageHandler::StaticCreateClass());

    // CD2 0x82FDFB08: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cDynamicBodycBodyInheritRegistrar(
        PHYSICS::cDynamicBody::StaticCreateClass(), PHYSICS::cBody::StaticCreateClass());

    // CD2 0x82FDF730: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cBodySpawningRegistrar(
        cBody::StaticCreateClass(), cBody::SpawnFromPrototype);

    const char *cBody::RetClassName() const
    {
        return "cBody";
    }

    cBody::~cBody()
    {
    }

    RWS::CAttributeHandler *cBody::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cBodyPrototype(packet);
    }

    Fun_Runtime::RetVal cBody::Init(const GOM::cSpawner *pSpawnArgs)
    {
        if (cGameBase::Init(pSpawnArgs) != Ret_OK)
            return Ret_FAIL;
        m_pRigidBody = 0;
        m_pMyWorld = 0;
        m_bSleeping = false;
        m_bSuspended = false;
        m_fSpeed = Fun_Runtime::g_GlobalConstants.CONST_FLOAT_0;
        m_fLastSpeed = Fun_Runtime::g_GlobalConstants.CONST_FLOAT_0;
        m_nActivationType = 0;
        m_bHasBeenNearLocalPlayer = false;
        m_CollisionListener.Init(this);
        return Ret_OK;
    }

    Fun_Runtime::RetVal cBody::Init(const RWS::CAttributePacket &attr)
    {
        cGameBase::Init(attr);
        m_pRigidBody = 0;
        m_pMyWorld = 0;
        m_fSpeed = Fun_Runtime::g_GlobalConstants.CONST_FLOAT_0;
        m_fLastSpeed = Fun_Runtime::g_GlobalConstants.CONST_FLOAT_0;
        m_nActivationType = 0;
        m_bHasBeenNearLocalPlayer = false;
        return Ret_OK;
    }

    Fun_Runtime::RetVal cBody::Term()
    {
        cGameBase::Term();
        return Ret_OK;
    }

    Fun_Runtime::RetVal cBody::Reinitialise(const GOM::cSpawner *pSpawnArgs)
    {
        m_fSpeed = Fun_Runtime::g_GlobalConstants.CONST_FLOAT_0;
        m_fLastSpeed = Fun_Runtime::g_GlobalConstants.CONST_FLOAT_0;
        m_nActivationType = 0;
        m_bHasBeenNearLocalPlayer = false;
        return cGameBase::Reinitialise(pSpawnArgs);
    }

    Fun_Runtime::RetVal cBody::TermForReuse()
    {
        m_bSuspended = false;
        cGameBase::TermForReuse();
        return Ret_OK;
    }

    void cBody::HandleAttributes(const RWS::CAttributePacket &attr)
    {
        cGameBase::HandleAttributes(attr);
    }

    RWS::CAttributeHandler *cBody::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cBody;
        return 0;
    }

    // CD2 script-type registration; constructor/table evidence identifies the child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cBody> cBodyScriptRegistrar(
        "cBody", "cGameBase");
}
