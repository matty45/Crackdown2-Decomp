// src/GameManagement/cTeamDeathMatchGameModePrototype.cpp
//
// Class: cTeamDeathMatchGameModePrototype (namespace: GameManagement). Set up automatically: no function is matched
// yet. The address range and the evidence for it are in config/splits.txt; RuffKing's object for it is
// cTeamDeathMatchGameMode.obj.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/GameManagement/cTeamDeathMatchGameModePrototype.cpp


// CD2 0x83018738 (initializer) and 0x83043DA8 (at-exit destructor).

#include "rws/classfactory.h"
#include "GameManagement/cTeamDeathMatchGameModePrototype.h"

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cTeamDeathMatchGameModePrototypeRegistrar(
        "cTeamDeathMatchGameModePrototype", cTeamDeathMatchGameModePrototype::MakeNew, 0x190, false);
}
