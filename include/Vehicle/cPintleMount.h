// Vehicle::cPintleMount (Crackdown 2): STAND-IN, name from RuffKing (cHelicopter::m_aTurrets is a cPintleMount[2]).
// Size 0x150: cHelicopter::RetPintleMount (0x826B8B10) indexes the array with that stride. Fields not modelled.
#ifndef Vehicle_cPintleMount_H
#define Vehicle_cPintleMount_H

#include "cd2/layout.h"

namespace Vehicle
{
    class cPintleMount
    {
    private:
        unsigned char m_unmodelled[0x150];

        CD2_LAYOUT_CHECKS(cPintleMount,
            CD2_SIZE(cPintleMount, 0x150))
    };
}

#endif
