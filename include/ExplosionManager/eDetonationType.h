// ExplosionManager::eDetonationType: RuffKing's enumeration (InitiateExplosion's first parameter); values not yet
// checked against CD2's code.
#ifndef EXPLOSIONMANAGER_EDETONATIONTYPE_H
#define EXPLOSIONMANAGER_EDETONATIONTYPE_H

namespace ExplosionManager
{
    enum eDetonationType
    {
        eDT_None = 0,
        eDT_Explosion,
        eDT_UV,
        eDT_Acid,
        eDT_FreakDeath,
        eDT_Water,
        eDT_HERound,
        eDT_Max
    };
}

#endif // EXPLOSIONMANAGER_EDETONATIONTYPE_H
