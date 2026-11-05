#include "rws/attributes.h"
// Cam::cCameraManager (Crackdown 2): interface stand-in. CD2 constructor 0x8252C1E0
// calls cNonGameBase's constructor and installs its five inherited interface tables.
// Instance fields are opaque; the allocation size is established by CD2's factory.
// StaticCreateClass (0x8252C070) builds cClass(0x622, "cCameraManager", 0x170); 0x170 is the size its registrar gives.
#ifndef CAM_CCAMERAMANAGER_H
#define CAM_CCAMERAMANAGER_H

#include "fun_runtime/class.h"
#include "gom/non_game_base.h"
#include "GameManagement/cGameModeArena.h"
#include "rws/logic.h"

namespace Cam
{
    class cCameraManager : public cNonGameBase
    {
    public:
        // CD2 0x8252C1E0: the allocation factory calls this constructor out of line.
        cCameraManager();
        // CD2 inlines this cleanup into the deleting wrapper at 0x8252C360.
        virtual ~cCameraManager()
        {
            UnLinkMsg(RWS::iMsgRunningPostTick);
            UnLinkMsg(RWS::iMsgPausedPostTick);
            sm_pInstance = 0;
        }
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        // RuffKing names; CD2 constructor stores this at 0x83800A70.
        static cCameraManager *RetInstance();
    private:
        static cCameraManager *sm_pInstance;
    public:
        // CD2 0x8252C028: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        // CD2 0x8252BF60: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x8252C018: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcCameraManagerClass;
        static Fun_Runtime::cClass &StaticCreateClass();

    private:
        // Descriptor and factory allocation agree on the complete size; own fields remain unrecovered.
        // CD2 uses the same standard pointer-list constructor/destructor as the
        // shared cList stand-in; these descriptive member names are ours.
        GameManagement::cList m_Cameras;
        unsigned char m_unmodelled88[0x160 - 0x88];
        GameManagement::cList m_SecondaryCameras;
        unsigned char m_unmodelled16C[4];
        CD2_LAYOUT_CHECKS(cCameraManager,
            CD2_SIZE(cCameraManager, 0x170)
            CD2_OFFSET(cCameraManager, m_Cameras, 0x7C)
            CD2_OFFSET(cCameraManager, m_SecondaryCameras, 0x160))
    };
}

#endif // CAM_CCAMERAMANAGER_H
