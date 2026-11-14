// Damage::cDamageMorphManager (Crackdown 2): names and layout from RuffKing (Damage/cDamageMorphManager.h, 0x8C bytes),
// confirmed by CD2: ClearMorphSections (0x825FC728) walks the sections from +8 for the count at +0x88 and clears the
// count, and CD2's table 0x8211EB08 has RuffKing's four virtuals (destructor 0x825FC0E0, Init 0x825FC0D8, ClearDamage
// 0x825FC4B8, ForceDamagedFraction 0x825FC7F8). RuffKing's destructor is out of line; CD2's vehicle and prop
// destructors (0x826CE0E8, 0x82729538) inline it as the table store and the ClearMorphSections call, so it is inline
// here.
#ifndef DAMAGE_CDAMAGEMORPHMANAGER_H
#define DAMAGE_CDAMAGEMORPHMANAGER_H

#include "cd2/layout.h"

namespace PHYSICS { class cDynamicBody; }

namespace Damage
{
    class cMorphSection;

    class cDamageMorphManager
    {
    public:
        cDamageMorphManager();
        virtual ~cDamageMorphManager() { ClearMorphSections(); }
        virtual void Init(PHYSICS::cDynamicBody *pParent);
        virtual void ClearDamage();
        virtual void ForceDamagedFraction(float fProportion);
        void ClearMorphSections();

    private:
        PHYSICS::cDynamicBody *m_pParent;               // 0x4
        cMorphSection *m_apMorphSections[32];           // 0x8
        unsigned char m_nNumMorphSections;              // 0x88

        CD2_LAYOUT_CHECKS(cDamageMorphManager,
            CD2_SIZE(cDamageMorphManager, 0x8C)
            CD2_OFFSET(cDamageMorphManager, m_apMorphSections, 8)
            CD2_OFFSET(cDamageMorphManager, m_nNumMorphSections, 0x88))
    };
}

#endif // DAMAGE_CDAMAGEMORPHMANAGER_H
