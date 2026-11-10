// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "unknown/cLaunchPadLocation.h"
#include "rws/classfactory.h"

namespace unknown
{
    const char *cLaunchPadLocation::RetClassName() const
    {
        return "cLaunchPadLocation";
    }

    cLaunchPadLocation::~cLaunchPadLocation()
    {
        if (m_pLaunchPad)
        {
            delete m_pLaunchPad;
            m_pLaunchPad = 0;
        }
    }

    static RWS::CClassFactory::CRegistrar cLaunchPadLocationRegistrar(
        "cLaunchPadLocation", cLaunchPadLocation::MakeNew, 0xA0, false);
}
