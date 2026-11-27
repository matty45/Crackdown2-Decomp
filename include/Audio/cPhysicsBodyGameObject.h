// Audio::cPhysicsBodyGameObject (Crackdown 2): STAND-IN. Name, base and constructor argument from RuffKing
// (Audio/cPhysicsBodyGameObject.h, 0x150 bytes there). CD2's is 0xC8 bytes: its constructor (0x82832DB0) stores
// fields up to +0xC5, and cProp embeds one at 0x7B8 with the next member at 0x880 (cProp's destructor, 0x82729538).
// The constructor stores its type argument at +0x90, which the RetType override (0x82833168) returns. CD2's table
// 0x8215A394 overrides only the destructor and RetType. The destructor is inline: the deleting destructor
// (0x82832E50) and the vehicle and prop destructors (0x826CE0E8, 0x82729538) store the table and call ~cGameObject.
#ifndef AUDIO_CPHYSICSBODYGAMEOBJECT_H
#define AUDIO_CPHYSICSBODYGAMEOBJECT_H

#include "Audio/cGameObject.h"

namespace Audio
{
    class cPhysicsBodyGameObject : public cGameObject
    {
    public:
        cPhysicsBodyGameObject(eGameObjectType eType);
        virtual ~cPhysicsBodyGameObject() {}
        virtual eGameObjectType RetType() const;
        // RuffKing's names; cProp's audio virtuals (0x82730470, 0x82730488, 0x827304A0) tail-call them.
        void ContinueScrapeNextUpdate(float fRelativeVelocity);    // CD2 0x8222B258
        void PostImpactEvent(float fImpulseValue);                 // CD2 0x82833098
        void PostPickedUpEvent() const;                            // CD2 0x82833118
        // Reference names. CD2's grenade water-audio virtuals inline the registration
        // guard and these two calls, with the incoming impulse left in f1.
        void PostWaterEntryEvent(float fImpulseValue)
        {
            if (IsRegistered())
            {
                SetRTPC(eRTPC_ImpulseValue, fImpulseValue);
                OneShot(eOSE_ObjectWaterIn);
            }
        }
        void PostWaterExitEvent(float fImpulseValue)
        {
            if (IsRegistered())
            {
                SetRTPC(eRTPC_ImpulseValue, fImpulseValue);
                OneShot(eOSE_ObjectWaterOut);
            }
        }
        // RuffKing's name: CD2 0x82832F98 posts the stop events and unregisters when registered (cHWGrenadeProjectile's
        // destructor 0x82629658 calls it on its member before destroying it).
        void Term();

    private:
        eGameObjectType m_eType;    // 0x90 (RuffKing's name)
        unsigned char m_unmodelled94[0xC8 - 0x94];

        CD2_LAYOUT_CHECKS(cPhysicsBodyGameObject,
            CD2_SIZE(cPhysicsBodyGameObject, 0xC8)
            CD2_OFFSET(cPhysicsBodyGameObject, m_eType, 0x90))
    };
}

#endif // AUDIO_CPHYSICSBODYGAMEOBJECT_H
