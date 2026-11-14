#include "rws/attributes.h"
// unknown::cVirtualCamera: interface stand-in. CD2 constructor 0x8230C710 calls
// cGameBase and constructs cDebugPageHandler at +0x120; inheritance registrars
// identify both bases. Its descriptor and MakeNew allocation establish size 0xF10;
// unrecovered instance fields remain opaque.
// StaticCreateClass (0x8252CE88) builds cClass(0x637, "cVirtualCamera", 0xF10); 0xF10 is the size its registrar gives.
#ifndef UNKNOWN_CVIRTUALCAMERA_H
#define UNKNOWN_CVIRTUALCAMERA_H

#include "fun_runtime/class.h"
#include "gom/game_base.h"
#include "GDb/cDebugPageHandler.h"

namespace unknown
{
    // Names ours, from CD2's console command "toggleh2hcamera" (0x82227BD0).
    // The shared switch at 0x830A3042 is initially true and read by camera updates.
    extern bool g_bH2HCameraEnabled;
    // "togglecamerasmooth" and its ON/OFF messages identify this shared switch.
    extern bool g_bCameraSmoothing;
    void AutoCamera(void *, wchar_t *);
    void FixedCamera(void *, wchar_t *);
    void FixedTrackingCamera(void *, wchar_t *);
    void SatelliteCamera(void *, wchar_t *);
    void FlyCamera(void *, wchar_t *);
    void ToggleCameraSmoothing(void *, wchar_t *);
    void ToggleH2HCamera(void *, wchar_t *);

    class cVirtualCamera : public cGameBase, public GDb::cDebugPageHandler
    {
    public:
        // Names ours, from console-command registrations and their mode arguments.
        enum eCameraMode
        {
            eAutomatic = 8, eFixed = 17, eFixedTracking = 18,
            eSatellite = 20, eFly = 22
        };
        // CD2 0x8252DB88 changes mode through 0x823632D0, then resets mode flags.
        void ChangeMode(eCameraMode);
        cVirtualCamera(); // CD2 0x8230C710, out of line
        void ToggleByte4E5();
        // CD2 0x8252CDD0: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        // CD2 0x8252CDC0: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcVirtualCameraClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    private:
        unsigned char m_unmodelled124[0x4E5 - 0x124];
        unsigned char m_byte4E5;                    // 0x4E5
        unsigned char m_unmodelled4E6[0xF10 - 0x4E6];
        CD2_LAYOUT_CHECKS(cVirtualCamera, CD2_SIZE(cVirtualCamera, 0xF10)
            CD2_OFFSET(cVirtualCamera, m_byte4E5, 0x4E5))
    };
}

#endif // UNKNOWN_CVIRTUALCAMERA_H
