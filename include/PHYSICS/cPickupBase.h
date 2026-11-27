// STAND-IN: RuffKing cPickupBase's base order and leading fields; CD2 descriptor 0x82709340 gives size 0x150. CD2's
// constructor (0x827093D8) initialises m_nID (-1), m_pNextPickup, m_ePickupType (-1), m_ePickupArea (-1), m_Position,
// m_bIsActive (1), m_pPickUpVFX, the draw/audible flags, m_fFadeTimer and m_bForceFadeIn at RuffKing's offsets less
// 0x30; RuffKing's Audio::cPickupGameObject m_WwiseGameObject follows at 0xB8 (its vptr), 8-byte aligned, and ends the
// class at 0x150. The destructor (0x82709638) stores the class's tables, destroys the audio object (its table, then
// ~cGameObject) and calls ~cNonGameBase.
#ifndef PHYSICS_CPICKUPBASE_H
#define PHYSICS_CPICKUPBASE_H
#include "gom/non_game_base.h"
#include "rws/systemcommands.h"
#include "fun_runtime/vec3.h"
#include "cd2/layout.h"
#include "Audio/cPickupGameObject.h"
namespace VFX
{
    class cParticleEffectInstance;
}
namespace Fun_Runtime { class cString; }
namespace PLAYER { class cPlayer; }
namespace PHYSICS
{
    class cPickupBase : public RWS::CSystemCommands, public cNonGameBase
    {
    public:
        // CD2 0x827093D8; its factory calls construction out of line.
        cPickupBase();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
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
        Audio::cPickupGameObject m_WwiseGameObject;
        // CD2: cPickupBase's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x827FBD60
        virtual Fun_Runtime::RetVal Init(RWS::CAttributePacket const &); // 5: 0x827097D8
        virtual Fun_Runtime::RetVal Term(); // 6: 0x827096B8
        virtual Fun_Runtime::Vec3 RetPosition() const; // 46: 0x827090F0
        virtual int RetUniqueID(); // CEventHandler 1: 0x82604E70
        virtual void HandleEvents(RWS::CMsg &); // CEventHandler 5: 0x82709930
        // CD2 0x82709000 / 0x82709010 (outside the scaffolded files): the registered-class pair of cPickupBase's table.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual Fun_Runtime::Vec3 RetScriptPosition() const; // cSafeDeletable 3: 0x827090C8

        // RuffKing's new virtuals, in its order, without RetCentre (a non-virtual script method in CD2): CD2's table
        // 0x82009E60 runs to slot 75. Slots 69 and 72 hold the shared return-true body, 73 and 74 the shared empty one.
        virtual void ReInit();                                                          // 68: 0x82709510
        virtual bool CanPickupNow() { return true; }                                    // 69 (RuffKing's inline)
        virtual void SetActive(bool bActive);                                           // 70: 0x82709D18
        virtual void GetVFXData(int &nEffectId, float &fPri, float &fScale);            // 71: 0x82709FC0
        virtual bool CanAutoPickup() const;                                             // 72
        virtual void GetLocPickupString(Fun_Runtime::cString &sLocString, bool &bHideButton) const {} // 73 (inline)
        virtual void Use(PLAYER::cPlayer *);                                            // 74
        virtual void Collect(PLAYER::cPlayer *pPlayer);                                 // 75: 0x821D1DF0
    private:
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
            CD2_OFFSET(cPickupBase, m_bForceFadeIn, 0xB0)
            CD2_OFFSET(cPickupBase, m_WwiseGameObject, 0xB8))
    };
}
#endif
