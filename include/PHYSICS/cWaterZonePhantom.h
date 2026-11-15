// STAND-IN: reference base order and parent pointer; CD2 0x827083F8 reads it at +0x70.
#ifndef PHYSICS_CWATERZONEPHANTOM_H
#define PHYSICS_CWATERZONEPHANTOM_H
#include "PHYSICS/cShapePhantomBodyWater.h"
namespace PHYSICS
{
    class cWaterZone;
    class cWaterZonePhantom : public cShapePhantomBodyWater
    {
    public:
        virtual void OnGameObjectEnter(cGameBase *);
        virtual void OnGameObjectLeave(cGameBase *);
        cWaterZone *m_pParent;
        CD2_LAYOUT_CHECKS(cWaterZonePhantom,
            CD2_SIZE(cWaterZonePhantom, 0x80)
            CD2_OFFSET(cWaterZonePhantom, m_pParent, 0x70))
    };
}
#endif
