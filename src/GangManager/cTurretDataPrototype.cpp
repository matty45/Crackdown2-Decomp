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
