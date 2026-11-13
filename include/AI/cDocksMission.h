#include "AI/cMission.h"
// Mission base restored from the registered parent and reference hierarchy; instance fields remain incomplete.
#ifndef AI_cDocksMission_H
#define AI_cDocksMission_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"
#include "fun_runtime/vectorip.h"
namespace Activity { class cTurretSpawnPoint; }
namespace Cam { class cCameraMarker; }

namespace AI
{
    class cDocksMission : public AI::cMission
    {
    public:
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcDocksMissionClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

        // RuffKing's states; CD2's delivery notifications (0x82474AB0, 0x82474AC0) enter eDMS_Complete.
        enum eDMState
        {
            eDMS_Inactive = 0,
            eDMS_CallingDrop,
            eDMS_AwaitingDelivery,
            eDMS_Complete,
            eDMS_NumStates,
            eDMS_Invalid,
        };

        virtual void TickUpdate(float dT);
        virtual void Activate();
        virtual void Deactivate();
        virtual void ResetMission();
        virtual void NotifyDeliveryStart(int nHeliID);
        virtual void NotifyDeliveryDrop(bool bSuccess);
        virtual void NotifyDeliveryFinish(bool bSuccess);
        virtual bool IsLocalPlayerNearby() const;
        unsigned int NumAssociatedMissionsComplete();   // CD2 0x82474A40
    protected:
        virtual void GetSaveStateForMissionState(unsigned char &nGlobalMissionState, unsigned char &nMissionState);
        void Update();                                  // CD2 0x824747D8
        void CheckForCameraCutActivation();             // CD2 0x82474AE0
        void CheckForCameraCutDeactivation();           // CD2 0x82474C00

        // RuffKing's fields; its size (0x450) is CD2's registrar size.
        cMissionCriticalPropSpawnPoint *m_pCollectionObject;            // 0x3C0
        unsigned int m_nHeliID;                                         // 0x3C4
        Fun_Runtime::cVectorip<cMission *, 5> m_vMissions;              // 0x3D0
        Fun_Runtime::cVectorip<Activity::cTurretSpawnPoint *, 5> m_vTurretList;     // 0x400
        Cam::cCameraMarker *m_pCameraMarker;                            // 0x430
        Cam::cCameraMarker *m_pCameraLookAtMarker;                      // 0x434
        float m_fCameraCutTriggerRadiusSq;                              // 0x438
        unsigned int m_nCameraCutEndTime;                               // 0x43C
        float m_fCameraCutHoldTime;                                     // 0x440
        bool m_bInCameraCut;                                            // 0x444
        CD2_LAYOUT_CHECKS(cDocksMission,
            CD2_SIZE(cDocksMission, 0x450)
            CD2_OFFSET(cDocksMission, m_nHeliID, 0x3C4)
            CD2_OFFSET(cDocksMission, m_vMissions, 0x3D0)
            CD2_OFFSET(cDocksMission, m_bInCameraCut, 0x444))
    };
}

#endif
