// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/cBreachHole.h"
#include "AI/cGoliathBreachHole.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace AI
{
    const Fun_Runtime::cClass *cGoliathBreachHole::ms_pcGoliathBreachHoleClass = &cGoliathBreachHole::StaticCreateClass();

    cGoliathBreachHole::cGoliathBreachHole() {}

    const Fun_Runtime::cClass &cGoliathBreachHole::RetClass() const
    {
        return *ms_pcGoliathBreachHoleClass;
    }

    const char *cGoliathBreachHole::RetClassName() const
    {
        return "cGoliathBreachHole";
    }

    bool cGoliathBreachHole::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcGoliathBreachHoleClass->IsA(c);
    }

    RWS::CAttributeHandler *cGoliathBreachHole::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cGoliathBreachHole();
    }

    static RWS::CClassFactory::CRegistrar cGoliathBreachHoleRegistrar(
        "cGoliathBreachHole", cGoliathBreachHole::MakeNew, 0x1D0, false);

    Fun_Runtime::cClass &cGoliathBreachHole::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cGoliathBreachHoleClass = new Fun_Runtime::cClass(0x9F37F, "cGoliathBreachHole", 0x1D0);
        return *cGoliathBreachHoleClass;
    }

    // CD2 0x82F8A090: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cGoliathBreachHolecBreachHoleInheritRegistrar(
        AI::cGoliathBreachHole::StaticCreateClass(), AI::cBreachHole::StaticCreateClass());
}
