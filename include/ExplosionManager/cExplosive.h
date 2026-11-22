// ExplosionManager::cExplosive (Crackdown 2): STAND-IN; names, types and order from RuffKing's
// ExplosionManager/cExplosive.h, modelled up to the explosion level. CD2's grenades and projectiles store their level
// at +0xD4 of the explosive they own (cExplosiveGrenade::SetExplosiveLevel 0x8261D690, cHWProjectile's
// SetExplosiveSkillLevel 0x8262B250), RuffKing's m_nLevel offset; the fields after it are not checked against CD2 yet.
#ifndef EXPLOSIONMANAGER_CEXPLOSIVE_H
#define EXPLOSIONMANAGER_CEXPLOSIVE_H

#include "cd2/layout.h"
#include "fun_runtime/mtx.h"
#include "fun_runtime/vec3.h"
#include "fun_runtime/safedeletablepointer.h"

class cGameBase;
namespace PHYSICS { class cBody; }
namespace CHARACTER { class cCharacterInterface; }

namespace ExplosionManager
{
    class cExplosionCallback;

    class cExplosive
    {
    public:
        virtual ~cExplosive();
        // RuffKing's (out of line there); CD2 expands it into its callers.
        void SetLevel(unsigned int nLevel) { m_nLevel = nLevel; }
        unsigned int RetLevel() const { return m_nLevel; }

    private:
        Fun_Runtime::Mtx m_mtxTransform;                                            // 0x10
        Fun_Runtime::Mtx m_mtxLocalOffset;                                          // 0x50
        Fun_Runtime::Vec3 m_vDecalPosition;                                         // 0x90
        Fun_Runtime::cSafeDeletablePointer<PHYSICS::cBody> m_pAttachObject;         // 0xA0
        Fun_Runtime::cSafeDeletablePointer<cGameBase> m_pInstigator;                // 0xB0
        Fun_Runtime::cSafeDeletablePointer<CHARACTER::cCharacterInterface> m_pAttacker; // 0xC0
        cExplosionCallback *m_pCallback;                                            // 0xD0
        unsigned int m_nLevel;                                                      // 0xD4

        CD2_LAYOUT_CHECKS(cExplosive,
            CD2_OFFSET(cExplosive, m_pCallback, 0xD0)
            CD2_OFFSET(cExplosive, m_nLevel, 0xD4))
    };
}

#endif // EXPLOSIONMANAGER_CEXPLOSIVE_H
