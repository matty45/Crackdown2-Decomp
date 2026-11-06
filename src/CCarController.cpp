// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "gom/proto_registrar.h"
#include "unknown/CCarController.h"
#include "fun_runtime/retval.h"
#include "fun_runtime/inheritance_registrar.h"
#include "VEHICLE_CONTROL/cHelicopterController.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace unknown
{
    Fun_Runtime::RetVal CCarController::cCarControllerPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }

    // src/CCarController.cpp
    //
    // Class: CCarController (namespace: unknown). Set up automatically: no function is matched yet. The address range and
    // the evidence for it are in config/splits.txt; RuffKing's object for it is CarController.obj.
    //
    // No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
    //
    // Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
    // include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
    //     py -I tools/cd2.py tasks src/CCarController.cpp
    const Fun_Runtime::cClass *CCarController::ms_pCCarControllerClass = &CCarController::StaticCreateClass();

    Fun_Runtime::cClass &CCarController::StaticCreateClass()
    {
        static Fun_Runtime::cClass *CCarControllerClass = new Fun_Runtime::cClass(0x929, "CCarController", 0xA30);
        return *CCarControllerClass;
    }

    static RWS::CClassFactory::CRegistrar CCarControllerRegistrar(
        "CCarController", CCarController::MakeNew, 0xA30, false);

    // CD2 0x83004B28: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar CCarControllercVehicleControllerInheritRegistrar(
        unknown::CCarController::StaticCreateClass(), VEHICLE_CONTROL::cVehicleController::StaticCreateClass());

    // CD2 0x83004BE0: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar CCarControllerSpawningRegistrar(
        CCarController::StaticCreateClass(), CCarController::SpawnFromPrototype);

    RWS::CAttributeHandler *CCarController::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cCarControllerPrototype(packet);
    }

    const char *CCarController::RetClassName() const
    {
        return "CCarController";
    }

    const Fun_Runtime::cClass &CCarController::RetClass() const
    {
        return *ms_pCCarControllerClass;
    }

    RWS::CAttributeHandler *CCarController::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) CCarController;
        return 0;
    }

    void CCarController::SetAssumedBrakingScale(float fBrakeFactor)
    {
        m_fAssumedBraking = fBrakeFactor;
    }

    void CCarController::SetLateralAccelScale(float fLatAccelScale)
    {
        m_fLateralAccelScale = fLatAccelScale;
    }

    float CCarController::GetAssumedBrakingScale()
    {
        return m_fAssumedBraking;
    }

    float CCarController::GetLateralAccelScale()
    {
        return m_fLateralAccelScale;
    }

    float CCarController::GetSpeedLimit()
    {
        return m_fMaxSpeed;
    }

    void CCarController::EnableTraining()
    {
        m_bTrainingEnabled = true;
    }

    void CCarController::DisableTraining()
    {
        m_bTrainingEnabled = false;
    }

    bool CCarController::IsTraining()
    {
        return m_bTrainingEnabled;
    }

    void CCarController::SetMaxLateralAccelAtSpeed(float fIn)
    {
        m_fLateralAccel = fIn;
    }

    void CCarController::SetMaxBrakingAccelAtSpeed(float fIn)
    {
        m_fBrakingAccel = fIn;
    }

    float CCarController::GetMaxLateralAccelAtSpeed(float)
    {
        return m_fLateralAccel;
    }

    float CCarController::GetMaxBrakingAccelAtSpeed(float)
    {
        return m_fBrakingAccel;
    }

    float CCarController::GetTargetSpeed()
    {
        return m_fTargetSpeed;
    }

    float CCarController::RetFrictionFactor()
    {
        return m_fFrictionFactor;
    }

    void CCarController::SetSpeedLimit(float fSpeed)
    {
        m_fMaxSpeed = fSpeed;
    }

    float CCarController::GetSteeringGainEstimate()
    {
        return m_fOverallSteeringResponse;
    }

    void CCarController::ResetSpeedLimit()
    {
        m_fMaxSpeed = m_fCarsTopSpeed;
    }
}
