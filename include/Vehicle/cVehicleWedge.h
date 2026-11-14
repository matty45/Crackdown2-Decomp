// Vehicle::cVehicleWedge (Crackdown 2): RuffKing's and Burn's cVehicleWedge.h name the class, its Havok listener base
// and its one field (8 bytes). CD2's cAgencySports constructor (0x826ED3E8) expands the constructor (table 0x821392E0,
// rigid body cleared) and its deleting destructor (0x826ED4C8) the destructor: RemoveWedge (0x82701218), then
// hkCollisionListener's table. Table 0x821392E0: contactPointAddedCallback 0x827013D8, the three other callbacks at
// the shared empty body 0x82580578, the deleting destructor 0x827007A8. Update (0x82701288) is RuffKing's
// Update(cVehicle *, float).
#ifndef VEHICLE_CVEHICLEWEDGE_H
#define VEHICLE_CVEHICLEWEDGE_H

#include "cd2/layout.h"
#include "Havok/hkCollisionListener.h"

class hkRigidBody;

namespace Vehicle
{
    class cVehicle;

    class cVehicleWedge : public hkCollisionListener
    {
    public:
        cVehicleWedge() : m_pWedgeRigidBody(0) {}
        virtual ~cVehicleWedge() { RemoveWedge(); }
        void RemoveWedge();
        void Update(cVehicle *pOwner, float dt);

    private:
        virtual void contactPointAddedCallback(hkContactPointAddedEvent &eventAdd);
        virtual void contactPointRemovedCallback(hkContactPointRemovedEvent &) {}
        virtual void contactProcessCallback(hkContactProcessEvent &) {}
        virtual void contactPointConfirmedCallback(hkContactPointConfirmedEvent &) {}

        hkRigidBody *m_pWedgeRigidBody;                 // 0x4

        CD2_LAYOUT_CHECKS(cVehicleWedge,
            CD2_SIZE(cVehicleWedge, 0x8)
            CD2_OFFSET(cVehicleWedge, m_pWedgeRigidBody, 0x4))
    };
}

#endif // VEHICLE_CVEHICLEWEDGE_H
