// PHYSICS::cCollisionListener: STAND-IN, names and layout from RuffKing (0xC bytes: hkCollisionListener, m_pBody,
// m_pRigidBody). CD2 embeds it in cBody at 0x240: cBody's constructor (0x82683400) installs its table 0x821327EC
// and clears m_pBody; cBody's destructor (0x826837D8) inlines the destructor, which clears m_pBody again before the
// Havok base's table is restored. RuffKing's destructor is out of line; CD2's is inlined, so it is inline here.
#ifndef PHYSICS_CCOLLISIONLISTENER_H
#define PHYSICS_CCOLLISIONLISTENER_H

#include "Havok/hkCollisionListener.h"
#include "cd2/layout.h"

class hkRigidBody;

namespace PHYSICS
{
    class cBody;

    class cCollisionListener : public hkCollisionListener
    {
    public:
        virtual ~cCollisionListener() { m_pBody = 0; }
        // RuffKing's Init(cBody *) is out of line; CD2 inlines it into cBody's Init (0x826835E0) as one store.
        void Init(cBody *pBody) { m_pBody = pBody; }
        virtual void contactPointAddedCallback(hkContactPointAddedEvent &);
        virtual void contactPointRemovedCallback(hkContactPointRemovedEvent &);
        virtual void contactProcessCallback(hkContactProcessEvent &);
        virtual void contactPointConfirmedCallback(hkContactPointConfirmedEvent &);

    private:
        cBody *m_pBody;             // 0x4
        hkRigidBody *m_pRigidBody;  // 0x8

        CD2_LAYOUT_CHECKS(cCollisionListener,
            CD2_SIZE(cCollisionListener, 0xC)
            CD2_OFFSET(cCollisionListener, m_pBody, 0x4))
    };
}

#endif // PHYSICS_CCOLLISIONLISTENER_H
