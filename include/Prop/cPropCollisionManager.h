// Prop::cPropCollisionManager (Crackdown 2): name, base and size (8) from RuffKing (Props/cPropCollisionManager.h),
// whose destructor is compiler-generated: cProp's destructor (0x82729538) destroys the one at 0xA24 by storing only
// hkCollisionListener's table. Its own overrides are not modelled yet.
#ifndef PROP_CPROPCOLLISIONMANAGER_H
#define PROP_CPROPCOLLISIONMANAGER_H

#include "Damage/cCollisionDamageListener.h"

namespace Prop
{
    class cPropCollisionManager : public Damage::cCollisionDamageListener
    {
        CD2_LAYOUT_CHECKS(cPropCollisionManager,
            CD2_SIZE(cPropCollisionManager, 8))
    };
}

#endif // PROP_CPROPCOLLISIONMANAGER_H
