// Havok action hierarchy from Burn/RuffKing. hkVehicleInstance's first own field at +0x1C
// confirms the complete hkUnaryAction base size in CD2.
#ifndef HAVOK_HKACTION_H
#define HAVOK_HKACTION_H
#include "Havok/hkReferencedObject.h"
#include "Havok/hkArray.h"
class hkEntity;
class hkPhantom;
class hkStepInfo;
class hkWorld;
class hkSimulationIsland;
class hkAction : public hkReferencedObject
{
public:
    virtual ~hkAction();
    virtual void applyAction(const hkStepInfo &) = 0;
    virtual void getEntities(hkArray<hkEntity *> &) = 0;
    virtual void getPhantoms(hkArray<hkPhantom *> &);
    virtual void entityRemovedCallback(hkEntity *) = 0;
    virtual hkAction *clone(const hkArray<hkEntity *> &, const hkArray<hkPhantom *> &) = 0;
private:
    hkWorld *m_world;
    hkSimulationIsland *m_island;
protected:
    unsigned int m_userData;
    const char *m_name;
    CD2_LAYOUT_CHECKS(hkAction,
        CD2_SIZE(hkAction, 0x18)
        CD2_OFFSET(hkAction, m_world, 8)
        CD2_OFFSET(hkAction, m_name, 0x14))
};
#endif
