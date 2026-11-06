// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "GangManager/cTurretDataPrototype.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace GangManager
{
    cTurretDataPrototype::~cTurretDataPrototype()
    {
        if (m_apGunners)
        {
            delete [] m_apGunners;
            m_apGunners = 0;
        }
    }

    const char *cTurretDataPrototype::RetClassName() const
    {
        return "cTurretDataPrototype";
    }

    static RWS::CClassFactory::CRegistrar cTurretDataPrototypeRegistrar(
        "cTurretDataPrototype", cTurretDataPrototype::MakeNew, 0x40, false);
}
