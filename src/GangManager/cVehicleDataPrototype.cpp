// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "GangManager/cVehicleDataPrototype.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace GangManager
{
    cVehicleDataPrototype::~cVehicleDataPrototype()
    {
        if (m_apOccupants)
        {
            delete [] m_apOccupants;
            m_apOccupants = 0;
        }
    }

    const char *cVehicleDataPrototype::RetClassName() const
    {
        return "cVehicleDataPrototype";
    }

    static RWS::CClassFactory::CRegistrar cVehicleDataPrototypeRegistrar(
        "cVehicleDataPrototype", cVehicleDataPrototype::MakeNew, 0x58, false);
}
