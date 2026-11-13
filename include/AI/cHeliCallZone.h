#ifndef AI_CHELICALLZONE_H
#define AI_CHELICALLZONE_H

#include "ZoneManager/cPlayerTriggerCylinder.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/memory.h"
#include "editor/guid_event_handler.h"

namespace VFX { class cParticleEffectInstance; }
namespace Cam { class cCameraMarker; }

namespace AI
{
    // RuffKing's base. CD2's table (0x82105878) has the trigger cylinder's 18 slots, then this class's RetClass, IsA,
    // RetClassName and Destruct in slots 18 to 21.
    class cHeliCallZone : public ZoneManager::cPlayerTriggerCylinder
    {
    public:
        static __forceinline Fun_Runtime::cClass &StaticCreateClass()
        {
            // CD2 inlines the local-static guard and descriptor creation into the global initializer (0x82F8EEC0);
            // /Ob1 declines a plain inline function here, and CD2 keeps no separate copy.
            static Fun_Runtime::cClass *cHeliCallZoneClass = new Fun_Runtime::cClass(0x85D0F, "cHeliCallZone", 0x1F0);
            return *cHeliCallZoneClass;
        }
        static const Fun_Runtime::cClass *ms_pcHeliCallZoneClass;
        // RuffKing name: the zone the player is in, set by OnPlayerEnter (CD2 0x8248AA18) and cleared by OnPlayerLeave.
        static cHeliCallZone *m_pCurrentCallZone;
        // RuffKing's name; CD2 0x8248AA58 (outside the scaffolded files), called by cTacticalObjective's
        // OnLeaveGlobalMissionState (0x82476228) as RuffKing's is.
        void Hide();

        cHeliCallZone();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        virtual void Destruct();
        // cPlayerTriggerBase's pure virtuals.
        virtual void OnPlayerEnter(CHARACTER::cCharacter *);
        virtual void OnPlayerLeave(CHARACTER::cCharacter *);
        // CD2: cHeliCallZone's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x821F8630
        virtual void InitTriggerZone(); // 14: 0x82787050
        virtual void TermTriggerZone(); // 15: 0x8248AA38

    private:
        // RuffKing's fields up to its audio object, at the same offsets in CD2 (0x8248A488 reads the state at 0xF0, the
        // called flag at 0xF4, the camera-cut fields at 0x130/0x134). CD2's class is 0x1F0 bytes (registrar, MakeNew
        // 0x8248A430) where RuffKing's is 0x1A0: its destructor (0x8248A598) destroys the audio object at 0x140 and the
        // GUID handler at 0x1D0, so CD2's audio object is 0x90 bytes.
        int m_eUserControlState;                        // 0xF0 RuffKing: eUserControlState
        bool m_bHasCalled;                              // 0xF4
        bool m_bOneOff;                                 // 0xF5
        float m_fMaxYScale;                             // 0xF8
        float m_fMaxXZScale;                            // 0xFC
        float m_fYOffset;                               // 0x100
        float m_fCurrentTime;                           // 0x104
        float m_fCooldownTime;                          // 0x108
        int m_nCallOnID;                                // 0x10C
        int m_nCallOffID;                               // 0x110
        VFX::cParticleEffectInstance *m_pCallOnVFX;     // 0x114
        VFX::cParticleEffectInstance *m_pCallOffVFX;    // 0x118
        unsigned int m_nHeliID;                         // 0x11C
        Cam::cCameraMarker *m_pCameraMarker;            // 0x120
        Cam::cCameraMarker *m_pCameraLookAtMarker;      // 0x124
        float m_fCameraCutTriggerRadiusSq;              // 0x128
        float m_fCameraCutHoldTime;                     // 0x12C
        unsigned int m_nCameraCutEndTime;               // 0x130
        bool m_bInCameraCut;                            // 0x134
        bool m_bInCameraCutStart;                       // 0x135
        float m_fCurrentTimer;                          // 0x138
        unsigned int m_nLocNameID;                      // 0x13C
        unsigned char m_HeliCallZoneAudio[0x90];        // 0x140 RuffKing: Audio::cGameObject; not modelled
        Editor::cGUIDEventHandler<cHeliCallZone> m_EventHandler;        // 0x1D0
        unsigned char m_unmodelled1E4[0x1F0 - 0x1E4];

        CD2_LAYOUT_CHECKS(cHeliCallZone,
            CD2_SIZE(cHeliCallZone, 0x1F0)
            CD2_OFFSET(cHeliCallZone, m_eUserControlState, 0xF0)
            CD2_OFFSET(cHeliCallZone, m_nCameraCutEndTime, 0x130)
            CD2_OFFSET(cHeliCallZone, m_EventHandler, 0x1D0))
    };
}

#endif

