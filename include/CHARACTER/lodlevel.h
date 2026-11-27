// CHARACTER::eLODLevel (Crackdown 2): RuffKing's character LOD enumeration (exported types), the type of
// AI::cMoveAgent::m_ePreviousLOD. The header name is ours.
#ifndef CHARACTER_LODLEVEL_H
#define CHARACTER_LODLEVEL_H

namespace CHARACTER
{
    enum eLODLevel
    {
        eLOD_0 = 0,
        eLOD_1,
        eLOD_2,
        eLOD_3,
        eLOD_4,
        eLOD_5,
        eNumLODLevels,
    };
}

#endif // CHARACTER_LODLEVEL_H
