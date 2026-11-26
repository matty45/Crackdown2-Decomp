// WorldManager::cEnvironmentWorldMap (Crackdown 2): STAND-IN for its size and destructor. RuffKing's derives from
// Activity::cOctree and keeps its environment-block vector at +0x20 (0x30 bytes); CD2's destructor (0x82807598)
// restores its table, frees that vector's storage (+0x24) and calls the octree's destructor (0x823D7A60).
// cWorldManager holds one at +0x970.
#ifndef WORLDMANAGER_CENVIRONMENTWORLDMAP_H
#define WORLDMANAGER_CENVIRONMENTWORLDMAP_H

#include "cd2/layout.h"

namespace WorldManager
{
    class cEnvironmentWorldMap
    {
    public:
        virtual ~cEnvironmentWorldMap();
    private:
        // The octree base and the block vector are not modelled.
        unsigned char m_unmodelled4[0x30 - 4];
        CD2_LAYOUT_CHECKS(cEnvironmentWorldMap, CD2_SIZE(cEnvironmentWorldMap, 0x30))
    };
}

#endif // WORLDMANAGER_CENVIRONMENTWORLDMAP_H
