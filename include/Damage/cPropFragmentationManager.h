// Damage::cPropFragmentationManager (Crackdown 2): names, layout (0x10C bytes) and virtual order from RuffKing
// (Damage/cPropFragmentationManager.h). CD2's table 0x8211ED20 has RuffKing's six slots: the deleting destructor
// (0x826039F8), CopyFragmentInfoFrom from a vehicle damage manager (0x82603C20, reads its count at +0x389) and from
// another fragmentation manager (0x82603B28, reads m_nNumComponents at +0x108), then 0x82603D18, 0x82603F28 and
// 0x826041F8. Both copies start with ClearComponents (0x82603A58). RuffKing's destructor is out of line; cProp's
// destructor (0x82729538) inlines it as the table store and the ClearComponents call, so it is inline here.
#ifndef DAMAGE_CPROPFRAGMENTATIONMANAGER_H
#define DAMAGE_CPROPFRAGMENTATIONMANAGER_H

#include "cd2/layout.h"

namespace Prop { class cProp; }

namespace Damage
{
    class cComponent;
    class cVehicleDamageManager;

    class cPropFragmentationManager
    {
    private:
        Prop::cProp *m_pProp;                           // 0x4
        cComponent *m_apComponentInfo[64];              // 0x8
        unsigned char m_nNumComponents;                 // 0x108
        unsigned char m_nRootFragmentIndex;             // 0x109
        bool m_bHasBrokenApart;                         // 0x10A
    public:
        cPropFragmentationManager();
        virtual ~cPropFragmentationManager() { ClearComponents(); }
        virtual void CopyFragmentInfoFrom(cVehicleDamageManager *pCarDM, unsigned int nRootHashname);
        virtual void CopyFragmentInfoFrom(cPropFragmentationManager *pFragManager, unsigned int nRootHashname);
        virtual void PostCreatePhysics();
        virtual void UpdateParentPostFragmentation();
        virtual void ResetParentPhysics();
        void ClearComponents();

        CD2_LAYOUT_CHECKS(cPropFragmentationManager,
            CD2_SIZE(cPropFragmentationManager, 0x10C)
            CD2_OFFSET(cPropFragmentationManager, m_nNumComponents, 0x108))
    };
}

#endif // DAMAGE_CPROPFRAGMENTATIONMANAGER_H
