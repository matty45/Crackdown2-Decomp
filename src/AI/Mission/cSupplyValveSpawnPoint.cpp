// AI/Mission/cSupplyValveSpawnPoint.cpp: RuffKing's Libraries/Shared/AI/Mission/cSupplyValveSpawnPoint.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "fun_runtime/class.h"
#include "fun_runtime/inheritance_registrar.h"
#include "rws/classfactory.h"
#include "AI/cSupplyValveSpawnPoint.h"
#include "cd2/memory.h"

namespace AI
{
    Fun_Runtime::cClass &cSupplyValveSpawnPoint::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cSupplyValveSpawnPointClass = new Fun_Runtime::cClass(0xDB7AE, "cSupplyValveSpawnPoint", 0x2E0);
        return *cSupplyValveSpawnPointClass;
    }

    const Fun_Runtime::cClass *cSupplyValveSpawnPoint::ms_pcSupplyValveSpawnPointClass = &cSupplyValveSpawnPoint::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cSupplyValveSpawnPointcRefineryPropSpawnPointInheritRegistrar(
        cSupplyValveSpawnPoint::StaticCreateClass(), cRefineryPropSpawnPoint::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cSupplyValveSpawnPointRegistrar(
        "cSupplyValveSpawnPoint", cSupplyValveSpawnPoint::MakeNew, 0x2E0, false);
}
