// src/Vehicle/cVehicle.cpp: Vehicle::cVehicle (include/Vehicle/cVehicle.h). The address range and its evidence are in
// config/splits.txt; RuffKing's object for it is cVehicle.obj. Definitions follow CD2's order: the static registrars'
// initializers (0x82FE9948..0x82FE9A70), then the functions from 0x826CC708.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "Vehicle/cVehicle.h"
#include "PHYSICS/cNetDynamicBody.h"
#include "rws/classfactory.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "fun_runtime/script_type_registrar.h"
#include "cd2/memory.h"
#include "VFX/cGlobalLight.h"
#include "Vehicle/cVehicleSeat.h"
#include <new>

namespace Vehicle
{
    const Fun_Runtime::cClass *cVehicle::ms_pcVehicleClass = &cVehicle::StaticCreateClass();

    // CD2 0x82FE9970: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cVehiclecNetDynamicBodyInheritRegistrar(
        cVehicle::StaticCreateClass(), PHYSICS::cNetDynamicBody::StaticCreateClass());

    // CD2 0x82FE99D8: the class factory builds a cVehiclePrototype from a packet.
    static RWS::CClassFactory::CRegistrar cVehicleRegistrar(
        "cVehicle", cVehicle::MakeNew, 0x1740, false);

    // CD2 0x82FE9A28: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cVehicleSpawningRegistrar(
        cVehicle::StaticCreateClass(), cVehicle::SpawnFromPrototype);

    // CD2 script-type registration names this child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cVehicle> cVehicleScriptRegistrar(
        "cVehicle", "cDynamicBody");

    const Fun_Runtime::cClass &cVehicle::RetClass() const
    {
        return *ms_pcVehicleClass;
    }

    RWS::CAttributeHandler *cVehicle::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cVehiclePrototype(packet);
    }

    const char *cVehicle::RetClassName() const
    {
        return "cVehicle";
    }

    RWS::CAttributeHandler *cVehicle::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cVehicle;
        return 0;
    }

    float cVehicle::RetTheoreticalMaxMPH()
    {
        return Fun_Runtime::g_GlobalConstants.CONST_FLOAT_0;
    }

    void cVehicle::SetIsBeingHiJackedByAI(bool bHiJacked)
    {
        m_bIsBeingHiJackedByAI = bHiJacked;
    }

    Fun_Runtime::cClass &cVehicle::StaticCreateClass()
    {
        static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x1, "cVehicle", 0x1740);
        return *descriptor;
    }
    const char *cVehicle::RetName() const
    {
        return m_strName.c_str();
    }

    bool cVehicle::CreateParts(const char **names, unsigned short count)
    {
        return LocateParts(names, count);
    }

    float cVehicle::RetFireRadius() const
    {
        return 1.5f;
    }

    void cVehicle::StartEngine()
    {
        SetEngineState(eENG_STARTING);
        m_fEngineHazeTimer = 30.0f;
    }

    void cVehicle::StopEngine()
    {
        if (m_eEngineState == eENG_STARTING || m_eEngineState == eENG_RUNNING)
            SetEngineState(eENG_STOPPING);
        m_bEngineShutdown = true;
    }

    int cVehicle::RetNumberOfSeats()
    {
        return m_VehicleSeats.size();
    }

    bool cVehicle::IsNearTurret(CHARACTER::cCharacter *pCharacter, unsigned int nTurret, char &nAttachPoint, float &fDist)
    {
        cVehiclePrototype *pPrototype = static_cast<cVehiclePrototype *>(m_pPrototype);
        return IsNearTurret(pCharacter, nTurret, pPrototype->m_VehicleSeatEntranceAngle,
            pPrototype->m_VehicleSeatEntranceXZDistTolerance, nAttachPoint, fDist);
    }

    unsigned int cVehicle::RetNumberOfOccupants()
    {
        unsigned int nOccupants = 0;
        for (unsigned int i = 0; i < m_VehicleSeats.size(); i++)
        {
            if (m_VehicleSeats[i]->RetOccupant())
                nOccupants++;
        }
        return nOccupants;
    }

    unsigned int cVehicle::RetSeatsInUse()
    {
        unsigned int nMask = 0;
        for (unsigned int i = 0; i < m_VehicleSeats.size(); i++)
        {
            if (m_VehicleSeats[i]->RetOccupant() || m_VehicleSeats[i]->RetInteractor())
                nMask |= 1 << i;
        }
        return nMask;
    }

    unsigned short cVehicle::RetCollisionSystemGroup()
    {
        return m_nSystemGroup;
    }

    void cVehicle::SetPhysicsLOD(unsigned char nNewLOD)
    {
        if (m_nPhysicsLOD != nNewLOD)
        {
            unsigned char nPrevLOD = m_nPhysicsLOD;
            m_nPhysicsLOD = nNewLOD;
            EventPhysicsLODChange(nPrevLOD, nNewLOD);
        }
    }

    unsigned char cVehicle::GetForceOpenMask()
    {
        unsigned char nMask = 0;
        for (int i = 0; i < 4; i++)
        {
            if (m_ForceOpen[i])
                nMask |= 1 << i;
        }
        return nMask;
    }

    bool cVehicle::IsLightActive(VFX::cGlobalLight *pLight, unsigned char, unsigned char)
    {
        if (pLight)
            return !pLight->IsDamaged();
        return true;
    }

    float cVehicle::RetNetworkDoorOpenCloseSpeed(unsigned char)
    {
        return 0.1f;
    }

}
