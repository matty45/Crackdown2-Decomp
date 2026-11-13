// Network::cNetRoleObject: an object's role in a networked game (authority, simulated, ...). Polymorphic base of every
// game object (cNonGameBase, at 0x38). Virtual order and layout from the RuffKing and Burn PDBs (they agree), confirmed
// by CD2's own vtable (0x82102E64): [destructor, SetNetRole, four empty OnEnterNetRole* handlers].
#ifndef NETWORK_NETROLE_H
#define NETWORK_NETROLE_H

#include "cd2/layout.h"

// RuffKing's enum names/order; CD2 time-of-day authority callback compares its role with 3.
enum etNetRole
{
    eNR_None = 0,
    eNR_DumbProxy,
    eNR_SimulatedProxy,
    eNR_Authority
};

namespace Network
{
    class cNetRoleObject
    {
    protected:
        etNetRole m_eNetRole;

    public:
        cNetRoleObject();
        // Descriptive accessor name is ours; exposes the reference-named role member.
        etNetRole RetNetRole() const { return m_eNetRole; }
        // RuffKing's name; CD2 expands it (cDocksMission::TickUpdate 0x82474790 compares the role with 3).
        bool IsAuthority() const { return m_eNetRole == eNR_Authority; }
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
