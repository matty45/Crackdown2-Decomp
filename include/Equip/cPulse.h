// Equip::cPulse (Crackdown 2): the pulse rifle's pulse, RuffKing's and Burn's names, base and member order. CD2's
// constructor (0x8260EE28) and destructor (0x8260EF58) give a 0x70-byte object, 0x10 more than RuffKing's: a second
// safe pointer follows the instigator at +0x5C and the active flag moves to +0x6C. cPulseRifle's placement factory
// (0x8260ED48) builds it at +0xA10.
#ifndef EQUIP_CPULSE_H
#define EQUIP_CPULSE_H

#include "cd2/layout.h"
#include "fun_runtime/safedeletablepointer.h"
#include "fun_runtime/vec3.h"
#include "fun_runtime/vector.h"
#include "PHYSICS/cPhysicsUniverse.h"
#include "Equip/tPulseProfile.h"

class hkAabbPhantom;
namespace CHARACTER { class cCharacter; }
namespace VFX { class cParticleEffectInstance; }

namespace Equip
{
    class cPulse : public PHYSICS::cPhysicsUniverse::cFindBodiesCallback
    {
    public:
        cPulse();
        virtual ~cPulse();
        bool IsActive() const { return m_bActive; }
        void Update(); // CD2 0x8260F378
        void Stop(); // CD2 0x8260F400
    private:
        void UpdatePulseVFX(); // CD2 0x8260F478
        void ReleasePulseVFX(); // CD2 0x8260F638
        virtual void BodyFoundCallback(PHYSICS::cBody *pBody);
        // CD2 0x8260F9C8: the character, vehicle and equipment tests pick target profiles 2, 1 and 3 (RuffKing's
        // attribute order: prop, vehicle, character, equipment); anything else is a prop.
        tPulseTargetProfile &RetPulseTargetProfile(PHYSICS::cBody *pBody) const;

        typedef Fun_Runtime::cVector<PHYSICS::cBody *> tBodyVector;
        tPulseProfile *m_pProfile;
        Fun_Runtime::Vec3 m_vPosition;
        Fun_Runtime::Vec3 m_vDirection;
        float m_fStartTime;
        hkAabbPhantom *m_pPhantom;
        tBodyVector m_vCollected;
        VFX::cParticleEffectInstance *m_pPulseVFX;
        Fun_Runtime::cSafeDeletablePointer<CHARACTER::cCharacter> m_pInstigator;
        // CD2 only; the name is ours. The body test (0x8260F7C0) skips the body this points at, comparing it with each
        // found PHYSICS::cBody pointer unconverted.
        Fun_Runtime::cSafeDeletablePointer<PHYSICS::cBody> m_pExcludedBody;
        bool m_bActive;

        CD2_LAYOUT_CHECKS(cPulse,
            CD2_SIZE(cPulse, 0x70)
            CD2_OFFSET(cPulse, m_pProfile, 0x4)
            CD2_OFFSET(cPulse, m_vPosition, 0x10)
            CD2_OFFSET(cPulse, m_vDirection, 0x20)
            CD2_OFFSET(cPulse, m_fStartTime, 0x30)
            CD2_OFFSET(cPulse, m_pPhantom, 0x34)
            CD2_OFFSET(cPulse, m_vCollected, 0x38)
            CD2_OFFSET(cPulse, m_pPulseVFX, 0x48)
            CD2_OFFSET(cPulse, m_pInstigator, 0x4C)
            CD2_OFFSET(cPulse, m_pExcludedBody, 0x5C)
            CD2_OFFSET(cPulse, m_bActive, 0x6C))
    };
}

#endif // EQUIP_CPULSE_H
