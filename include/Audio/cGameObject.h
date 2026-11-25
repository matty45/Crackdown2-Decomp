// Audio::cGameObject (Crackdown 2): STAND-IN. Name, the type enum and the first two virtuals from RuffKing
// (Audio/cGameObject.h, Audio/cPhysicsBodyGameObject.h); CD2's layout and table differ from RuffKing's. CD2's table
// 0x8215982C has five slots: the deleting destructor (0x8282FA18), RetType (0x825CCEB0, returns eGOT_Generic as
// RuffKing's value 6) and three slots whose bodies are not identified (0x82580578, 0x8282FA68, 0x82377B68). The
// destructor (0x8237A748) is out of line: cPhysicsBodyGameObject's inline destructor calls it from the vehicle's
// (0x826CE0E8); its body counts Burn's Audio::ScopedProfile references (0x838015E0) around RuffKing's IsRegistered/
// Unregister. cLandVehicle's destructor (0x826C2458) has that body expanded for its wheels, which only cross-module
// LTCG inlining of the out-of-line copy explains (an inline definition is expanded in the vehicle's too). Only the ID
// at +8 is modelled.
#ifndef AUDIO_CGAMEOBJECT_H
#define AUDIO_CGAMEOBJECT_H

#include "cd2/layout.h"

namespace Audio
{
    // CD2's RTPC descriptor 0x832A95A0 names entry 16 eRTPC_ImpulseValue.
    enum eRTPC
    {
        eRTPC_ImpulseValue = 16,
    };

    // CD2's one-shot table 0x820E50A0 supplies these names and indices.
    enum eOneShotEvent
    {
        eOSE_Training_GateClosed = 12,
        eOSE_ObjectWaterIn = 64,
        eOSE_ObjectWaterOut = 65,
    };

    // RuffKing's values (its PDB); CD2's base RetType returns 6.
    enum eGameObjectType
    {
        eGOT_AmbienceZone = 0,
        eGOT_AUMission,
        eGOT_BreachHole,
        eGOT_Character,
        eGOT_Exhaust,
        eGOT_Explosion,
        eGOT_Generic,
        eGOT_Grenade,
        eGOT_Light,
        eGOT_Marker,
        eGOT_ParticleEmitter,
        eGOT_Pickup,
        eGOT_Projectile,
        eGOT_Prop,
        eGOT_RadioStationObject,
        eGOT_SurfaceImpact,
        eGOT_Vehicle,
        eGOT_VOA,
        eGOT_Weapon,
        eGOT_Wheel,
        eGOT_WorldObject,
        eGOT_Max,
    };

    class cGameObject
    {
    public:
        virtual ~cGameObject();
        virtual eGameObjectType RetType() const;
        virtual void vf2();
        virtual void vf3();
        virtual void vf4();
        // RuffKing's (out of line there); CD2 inlines the ID test into the props' and vehicles' audio virtuals.
        bool IsRegistered() const { return m_id != (unsigned int)-1; }
        // CD2 0x822B3898 caches a typed RTPC value; 0x822C12E0 posts a table-indexed one-shot.
        void SetRTPC(eRTPC eParameter, float fValue);
        void OneShot(eOneShotEvent eEvent) const;

    private:
        unsigned char m_unmodelled4[4];
        unsigned int m_id;      // 0x8 (RuffKing's name)

        CD2_LAYOUT_CHECKS(cGameObject,
            CD2_OFFSET(cGameObject, m_id, 8))
    };
}

#endif // AUDIO_CGAMEOBJECT_H
