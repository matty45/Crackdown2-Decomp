// src/CHARACTER/cGenCharProfile.cpp
//
// Class: cGenCharProfile (namespace: CHARACTER). Set up automatically: no function is matched yet. The address range
// and the evidence for it are in config/splits.txt; RuffKing's object for it is cGenCharProfile.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Character/cGenCharProfile.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/CHARACTER/cGenCharProfile.cpp

#include "fun_runtime/inheritance_registrar.h"
#include "gom/non_game_base.h"
#include "rws/classfactory.h"
#include "CHARACTER/cGenCharProfile.h"
#include "cd2/memory.h"
#include "rws/msg.h"

namespace CHARACTER
{
    const char *cGenCharProfile::RetClassName() const
    {
        return "cGenCharProfile";
    }

    Fun_Runtime::cClass &cGenCharProfile::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cGenCharProfileClass = new Fun_Runtime::cClass(0x63F, "cGenCharProfile", 0x84);
        return *cGenCharProfileClass;
    }

    const Fun_Runtime::cClass *cGenCharProfile::ms_pcGenCharProfileClass = &cGenCharProfile::StaticCreateClass();

    static RWS::CClassFactory::CRegistrar cGenCharProfileRegistrar(
        "cGenCharProfile", cGenCharProfile::MakeNew, 0x84, false);

    // CD2 0x82FAEEC0: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cGenCharProfilecNonGameBaseInheritRegistrar(
        CHARACTER::cGenCharProfile::StaticCreateClass(), cNonGameBase::StaticCreateClass());

    // CD2 0x82556318: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cGenCharProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cGenCharProfile;
    }

    void cGenCharProfile::HandleEvents(RWS::CMsg &msg)
    {
        if (msg.Id == m_Msg_Return_Self)
            msg.pData = this;
    }
}
