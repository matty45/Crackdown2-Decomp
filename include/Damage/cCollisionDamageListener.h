// Damage::cCollisionDamageListener (Crackdown 2): STAND-IN. Name, base, size (8) and member from RuffKing
// (Damage/cCollisionDamageListener.h), whose destructor is compiler-generated: CD2's vehicle destructor (0x826CE0E8)
// destroys the one at 0x1108 by storing only hkCollisionListener's table (0x82114980). RuffKing's own virtuals follow
// the Havok callbacks; their CD2 slots are not checked yet.
#ifndef DAMAGE_CCOLLISIONDAMAGELISTENER_H
#define DAMAGE_CCOLLISIONDAMAGELISTENER_H

#include "Havok/hkCollisionListener.h"
#include "cd2/layout.h"

namespace PHYSICS { class cDynamicBody; class cBody; }
namespace Fun_Runtime { class Vec3; }

namespace Damage
{
    class cCollisionDamageListener : public hkCollisionListener
    {
    protected:
        PHYSICS::cDynamicBody *m_pParent;   // 0x4
    public:
        cCollisionDamageListener();
        virtual void Init(PHYSICS::cDynamicBody *pParent);
        virtual void ProcessCollisionDamage();
    protected:
        virtual void AddCollisionDamage(float, PHYSICS::cBody *, const Fun_Runtime::Vec3 &, const Fun_Runtime::Vec3 &);
        virtual void contactPointAddedCallback(hkContactPointAddedEvent &event);
        virtual void contactPointRemovedCallback(hkContactPointRemovedEvent &event);
        virtual void contactProcessCallback(hkContactProcessEvent &);
        virtual void contactPointConfirmedCallback(hkContactPointConfirmedEvent &event);

        CD2_LAYOUT_CHECKS(cCollisionDamageListener,
            CD2_SIZE(cCollisionDamageListener, 8)
            CD2_OFFSET(cCollisionDamageListener, m_pParent, 4))
    };
}

#endif // DAMAGE_CCOLLISIONDAMAGELISTENER_H
