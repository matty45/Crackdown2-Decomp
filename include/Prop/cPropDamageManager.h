// Prop::cPropDamageManager (Crackdown 2): names and layout (0x1A4 bytes) from RuffKing (Props/cPropDamageManager.h);
// CD2's cProp holds one at 0x880 with its collision manager at 0xA24, 0x1A4 bytes on, and cProp's destructor
// (0x82729538) destroys the fragmentation manager (+0x90) and then the morph manager (+4). Its destructor is
// compiler-generated, as RuffKing's. Only the members are modelled.
#ifndef PROP_CPROPDAMAGEMANAGER_H
#define PROP_CPROPDAMAGEMANAGER_H

#include "cd2/layout.h"
#include "Damage/cDamageMorphManager.h"
#include "Damage/cPropFragmentationManager.h"

namespace Prop
{
    class cProp;

    class cPropDamageManager
    {
    private:
        Damage::cDamageMorphManager m_DMManager;                // 0x4
        Damage::cPropFragmentationManager m_FragmentManager;    // 0x90
        cProp *m_pProp;                                         // 0x19C
        bool m_bComponentsSetup;                                // 0x1A0
    public:
        cPropDamageManager();
        virtual void Init(cProp *pProp);

        CD2_LAYOUT_CHECKS(cPropDamageManager,
            CD2_SIZE(cPropDamageManager, 0x1A4)
            CD2_OFFSET(cPropDamageManager, m_DMManager, 4)
            CD2_OFFSET(cPropDamageManager, m_FragmentManager, 0x90)
            CD2_OFFSET(cPropDamageManager, m_pProp, 0x19C))
    };
}

#endif // PROP_CPROPDAMAGEMANAGER_H
