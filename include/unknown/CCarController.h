// CD2 constructor 0x8277EFF0 confirms the shared base constructor chain.
#include "VEHICLE_CONTROL/cHelicopterController.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// unknown::CCarController (Crackdown 2): STAND-IN: constructor-confirmed base; remaining instance fields are not modelled.
// StaticCreateClass (0x8277ED80) builds cClass(0x929, "CCarController", 0xA30); 0xA30 is the size its registrar gives.
#ifndef UNKNOWN_CCARCONTROLLER_H
#define UNKNOWN_CCARCONTROLLER_H

#include "fun_runtime/class.h"

namespace unknown
{
    class CCarController : public VEHICLE_CONTROL::cVehicleController
    {
    public:
        // RuffKing names this prototype/base; CD2 MakeNew installs its table at 0x8214C0B8.
        // Interface only; complete instance storage is not recovered.
        class cCarControllerPrototype : public VEHICLE_CONTROL::cVehicleController::cVehicleControllerPrototype
        {
        public:
            // CD2's MakeNew (0x8277EC60) inlines this constructor: 0x70 bytes, cVehicleControllerPrototype's chain.
            __forceinline cCarControllerPrototype(const RWS::CAttributePacket &packet)
                : VEHICLE_CONTROL::cVehicleController::cVehicleControllerPrototype(packet) {}
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        };
        // CD2 factory 0x8277ECE0 forwards only this, without a prototype argument.
        CCarController();
        // CD2 0x8277EBF0: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x8277ECD0: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x83004BE0 names placement factory 0x8277ece0.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pCCarControllerClass;
        static Fun_Runtime::cClass &StaticCreateClass();

        // cVehicleController overrides; CD2 slot numbers. The names are RuffKing's (slot + 34 there).
        virtual void SetSpeedLimit(float);                      // 76
        virtual float GetSpeedLimit();                          // 77
        virtual void ResetSpeedLimit();                         // 78
        virtual bool IsTraining();                              // 84
        virtual void EnableTraining();                          // 85
        virtual void DisableTraining();                         // 86
        virtual float GetTargetSpeed();                         // 90
        virtual void SetAssumedBrakingScale(float);             // 92
        virtual void SetLateralAccelScale(float);               // 93
        virtual float GetAssumedBrakingScale();                 // 94
        virtual float GetLateralAccelScale();                   // 95
        virtual void SetMaxLateralAccelAtSpeed(float);          // 96
        virtual void SetMaxBrakingAccelAtSpeed(float);          // 97
        virtual float GetSteeringGainEstimate();                // 98
        virtual float GetMaxLateralAccelAtSpeed(float);         // 100
        virtual float GetMaxBrakingAccelAtSpeed(float);         // 101
        virtual float RetFrictionFactor();                      // 102

    private:
        // Fields the accessors above read and write. RuffKing's names: its block from m_fAssumedBraking (0x8E0) to
        // m_fBrakingAccel (0xA24) lies 0x30 bytes higher there, because its cVehicleController base is 0x30 larger.
        // The other fields are not recovered.
        unsigned char m_unmodelled840[0x8B0 - 0x840];
        float m_fAssumedBraking;                // 0x8B0
        unsigned char m_unmodelled8B4[0x8C0 - 0x8B4];
        float m_fLateralAccelScale;             // 0x8C0
        unsigned char m_unmodelled8C4[0x8D0 - 0x8C4];
        float m_fCarsTopSpeed;                  // 0x8D0 (ResetSpeedLimit copies it to m_fMaxSpeed)
        unsigned char m_unmodelled8D4[0x8DC - 0x8D4];
        float m_fFrictionFactor;                // 0x8DC
        bool m_bTrainingEnabled;                // 0x8E0
        unsigned char m_unmodelled8E1[0x8EC - 0x8E1];
        float m_fMaxSpeed;                      // 0x8EC (the speed limit)
        unsigned char m_unmodelled8F0[0x944 - 0x8F0];
        float m_fTargetSpeed;                   // 0x944
        unsigned char m_unmodelled948[0x958 - 0x948];
        float m_fOverallSteeringResponse;       // 0x958 (GetSteeringGainEstimate returns it)
        unsigned char m_unmodelled95C[0x9F0 - 0x95C];
        float m_fLateralAccel;                  // 0x9F0
        float m_fBrakingAccel;                  // 0x9F4
        unsigned char m_unmodelled9F8[0xA30 - 0x9F8];

        CD2_LAYOUT_CHECKS(CCarController,
            CD2_SIZE(CCarController, 0xA30)
            CD2_OFFSET(CCarController, m_fAssumedBraking, 0x8B0)
            CD2_OFFSET(CCarController, m_fLateralAccelScale, 0x8C0)
            CD2_OFFSET(CCarController, m_fCarsTopSpeed, 0x8D0)
            CD2_OFFSET(CCarController, m_fFrictionFactor, 0x8DC)
            CD2_OFFSET(CCarController, m_bTrainingEnabled, 0x8E0)
            CD2_OFFSET(CCarController, m_fMaxSpeed, 0x8EC)
            CD2_OFFSET(CCarController, m_fTargetSpeed, 0x944)
            CD2_OFFSET(CCarController, m_fOverallSteeringResponse, 0x958)
            CD2_OFFSET(CCarController, m_fLateralAccel, 0x9F0)
            CD2_OFFSET(CCarController, m_fBrakingAccel, 0x9F4))
    };
}

#endif // UNKNOWN_CCARCONTROLLER_H
