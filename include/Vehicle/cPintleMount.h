// Vehicle::cPintleMount (Crackdown 2): STAND-IN, name from RuffKing (cHelicopter::m_aTurrets is a cPintleMount[2]).
// Size 0x150: cHelicopter::RetPintleMount (0x826B8B10) indexes the array with that stride. Fields not modelled.
#ifndef Vehicle_cPintleMount_H
#define Vehicle_cPintleMount_H

#include "cd2/layout.h"
namespace Equip { class cCWWeapon; }
namespace Prop { class cPintleFaceplate; }
class cGameBase;
class cReplicatedClass;

namespace Vehicle
{
    class cPintleMount
    {
    public:
        // Reference names; CD2 car cleanup 0x826B6E70 forwards its flag to these two calls.
        void TerminateWeapon(bool);
        void TerminateFaceplate(bool);
        void Reset();
        Equip::cCWWeapon *m_pAttachedWeapon;
        Prop::cPintleFaceplate *m_pFacePlateProp;
    private:
        unsigned char m_unmodelled8[0xB4 - 8];
    public:
        // CD2 car cleanup clears these at +0xB4/+0xB8, agreeing with the reference members.
        cGameBase *m_pParent;
        cReplicatedClass *m_pReplicationHost;
    private:
        unsigned char m_unmodelledBC[0x150 - 0xBC];

        CD2_LAYOUT_CHECKS(cPintleMount,
            CD2_SIZE(cPintleMount, 0x150)
            CD2_OFFSET(cPintleMount, m_pAttachedWeapon, 0)
            CD2_OFFSET(cPintleMount, m_pFacePlateProp, 4)
            CD2_OFFSET(cPintleMount, m_pParent, 0xB4)
            CD2_OFFSET(cPintleMount, m_pReplicationHost, 0xB8))
    };
}

#endif
