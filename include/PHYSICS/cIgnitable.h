// STAND-IN: Burn virtual names/order; CD2 13-slot table 0x8213FDB0, object span 0x250..0x294.
#ifndef CD2_PHYSICS_CIGNITABLE_H
#define CD2_PHYSICS_CIGNITABLE_H
#include "fun_runtime/vec3.h"
#include "cd2/layout.h"
namespace CHARACTER { class cCharacter; }
namespace PHYSICS
{
    class cIgnitable
    {
    public:
        // RuffKing names the flag at +0x11; CD2's registered RetIsOnFire getter
        // reads it at cDynamicBody +0x261, after this base's +0x250 adjustment.
        bool IsOnFire() const { return m_bIsOnFire; }
        virtual ~cIgnitable();
        virtual float RetCatchFireTime() const;
    protected:
        virtual void UpdateIgnitable(float);
        virtual void PostTickIgnitable(float);
        virtual Fun_Runtime::Vec3 RetIgnitablePosition() const;
        virtual float RetFireRadius() const;
        virtual bool CanDoFireDamage() const;
        virtual bool CanCatchFireOnTouch() const;
        virtual float RetFireDamageModifier() const;
        virtual float RetTimeTillCatchFire() const;
        virtual void EventTriggerStartFire(CHARACTER::cCharacter *);
        virtual void EventTriggerOnFire();
        virtual void EventTriggerEndFire();
    private:
        unsigned char m_unknown4[0x11 - 4];
        bool m_bIsOnFire;
        unsigned char m_unknown12[0x44 - 0x12];
        CD2_LAYOUT_CHECKS(cIgnitable,
            CD2_SIZE(cIgnitable, 0x44)
            CD2_OFFSET(cIgnitable, m_bIsOnFire, 0x11))
    };
}
#endif
