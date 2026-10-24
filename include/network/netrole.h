// Network::cNetRoleObject: an object's role in a networked game (authority, simulated, ...). Polymorphic base of every
// game object (cNonGameBase, at 0x38). Virtual order and layout from the RuffKing and Burn PDBs (they agree), confirmed
// by CD2's own vtable (0x82102E64): [destructor, SetNetRole, four empty OnEnterNetRole* handlers].
#ifndef NETWORK_NETROLE_H
#define NETWORK_NETROLE_H

#include "cd2/layout.h"

enum etNetRole { };

namespace Network
{
    class cNetRoleObject
    {
    protected:
        etNetRole m_eNetRole;

    public:
        cNetRoleObject();
        virtual ~cNetRoleObject();
        virtual void SetNetRole(etNetRole);
        virtual void OnEnterNetRoleAuthority(etNetRole);
        virtual void OnEnterNetRoleSimulated(etNetRole);
        virtual void OnEnterNetRoleDumb(etNetRole);
        virtual void OnEnterNetRoleNone(etNetRole);

        CD2_LAYOUT_CHECKS(cNetRoleObject,
            CD2_SIZE(cNetRoleObject, 0x8)
            CD2_OFFSET(cNetRoleObject, m_eNetRole, 0x4))
    };
}

#endif // NETWORK_NETROLE_H
