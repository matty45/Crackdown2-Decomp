// STAND-IN: RuffKing cPickupBase's base order and leading fields; CD2 descriptor 0x82709340 gives size 0x150. CD2's
// constructor (0x827093D8) initialises m_nID (-1), m_pNextPickup, m_ePickupType (-1), m_ePickupArea (-1), m_Position,
// m_bIsActive (1), m_pPickUpVFX, the draw/audible flags, m_fFadeTimer and m_bForceFadeIn at RuffKing's offsets less
// 0x30; RuffKing's Audio::cPickupGameObject m_WwiseGameObject follows at 0xB8 (its vptr) and is not modelled yet.
#ifndef PHYSICS_CPICKUPBASE_H
#define PHYSICS_CPICKUPBASE_H
#include "gom/non_game_base.h"
#include "rws/systemcommands.h"
#include "fun_runtime/vec3.h"
#include "cd2/layout.h"
namespace VFX
{
    class cParticleEffectInstance;
}
namespace PHYSICS
{
    class cPickupBase : public RWS::CSystemCommands, public cNonGameBase
    {
    public:
        // CD2 0x82709638 (out of line: cAudioLog's destructor 0x8270EC18 calls it).
        virtual ~cPickupBase();
        static Fun_Runtime::cClass &StaticCreateClass();
    private:
        // Name ours: CD2's constructor leaves 0x7C untouched and starts at m_nID (0x80). RuffKing has the same 4-byte gap
        // after cNonGameBase (its 1-byte CSystemCommands base taking a slot); this compiler overlaps an empty base instead.
        unsigned int m_unknown7C;
    public:
        int m_nID;
    protected:
        cPickupBase *m_pNextPickup;
        int m_ePickupType;
        int m_ePickupArea; // RuffKing: PHYSICS::eArea
        Fun_Runtime::Vec3 m_Position;
        bool m_bIsActive;
        VFX::cParticleEffectInstance *m_pPickUpVFX;
        bool m_bDrawPickup;
        bool m_bPickupAudible;
        float m_fFadeTimer;
        bool m_bForceFadeIn;
    private:
        unsigned char m_unmodelledB4[0x150 - 0xB4];
        CD2_LAYOUT_CHECKS(cPickupBase,
            CD2_SIZE(cPickupBase, 0x150)
            CD2_OFFSET(cPickupBase, m_nID, 0x80)
            CD2_OFFSET(cPickupBase, m_pNextPickup, 0x84)
            CD2_OFFSET(cPickupBase, m_ePickupType, 0x88)
            CD2_OFFSET(cPickupBase, m_ePickupArea, 0x8C)
            CD2_OFFSET(cPickupBase, m_Position, 0x90)
            CD2_OFFSET(cPickupBase, m_bIsActive, 0xA0)
            CD2_OFFSET(cPickupBase, m_pPickUpVFX, 0xA4)
            CD2_OFFSET(cPickupBase, m_bDrawPickup, 0xA8)
            CD2_OFFSET(cPickupBase, m_bPickupAudible, 0xA9)
            CD2_OFFSET(cPickupBase, m_fFadeTimer, 0xAC)
            CD2_OFFSET(cPickupBase, m_bForceFadeIn, 0xB0))
    };
}
#endif
