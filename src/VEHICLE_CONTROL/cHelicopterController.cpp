// VEHICLE_CONTROL/cHelicopterController.cpp: cHelicopterController of Crackdown 2.
// Measurement batch 2 (2026-10-23, Sonnet 5.5): 17 functions byte-exact, 1 tracked as work in progress
// (config/matched_functions.json). Unknown bases and callees are stand-ins named in the header; out-of-line
// callees without a known name are declared as Ext_<address>.
// VEHICLE_CONTROL/cHelicopterController.cpp: AI helicopter flight controller (measurement batch 2).
#include "VEHICLE_CONTROL/cHelicopterController.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include <new>
#include <math.h>

extern int g_nVehicleTypeTag;      // 0x83847CA8
// Ret_OK and Ret_FAIL (fun_runtime/retval.h): this file's copies are at 0x8385253C and 0x8320731C

namespace VEHICLE_CONTROL
{
    const char *const cHelicopterController::pcHelicopterControllerClassID = "cHelicopterController";

    RWS::CAttributeHandler *cHelicopterController::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cHelicopterControllerPrototype(packet);
    }

    const char *cHelicopterController::RetClassName() const
    {
        return pcHelicopterControllerClassID;
    }

    cHelicopterController *cHelicopterController::SpawnFromPrototype(GOM::cObjectPrototype *proto, void *mem)
    {
        return new (mem) cHelicopterController;
    }

    float cHelicopterController::GetSpeedLimit()
    {
        return m_fMaxSpeed;
    }

    void cHelicopterController::ResetSpeedLimit()
    {
        m_fMaxSpeed = m_fDefaultMaxSpeed;
    }

    Fun_Runtime::cClass &cHelicopterController::StaticCreateClass()
    {
        static Fun_Runtime::cClass *pClass = new Fun_Runtime::cClass(2399, "cHelicopterController", 2240);
        return *pClass;
    }

    void cHelicopterController::SetSpeedLimit(float f)
    {
        m_fMaxSpeed = f;
    }

    Fun_Runtime::RetVal cHelicopterController::Term()
    {
        cVehicleController::Term();
        return Ret_OK;
    }

    void cHelicopterController::AssignVehicle(Vehicle::cVehicle *pVehicle)
    {
        m_pVehicle = pVehicle;
        Vehicle::cVehicle *v = (pVehicle && pVehicle->IsKindOf(g_nVehicleTypeTag)) ? pVehicle : 0;
        float f = v->m_pPhysics->m_fMaxSpeed;
        m_pVehicleRaw = pVehicle;
        m_fDefaultMaxSpeed = f;
    }

    cHelicopterController::cHelicopterController()
    {
        m_bFlag7D = true;
        m_bFlag7C = true;
        m_iCurrentWaypoint = -1;
        m_bTransitionToSimpleWhenPossible = true;
        m_fMaxSpeed = 100.0f;
        m_bTransitionToPhysicalWhenPossible = true;
        m_fMinControlCalcDist = 0.001f;
        m_bMaintainHeadingInSimple = false;
        m_fMinYawCalcDist = 3.0f;
        m_fStrafeControlCapability = 0.7f;
        m_fPitchControlCapability = 0.7f;
        m_fYawControlCapability = 0.7f;
        m_fLiftControlCapability = 1.0f;
        m_fCubicFractionalLookahead = 0.6f;
        m_fMaxLookAhead = 50.0f;
        m_fMinLookAhead = 35.0f;
        m_fLookaheadTweak = 2.0f;
        m_fYawOnlyNoThrustLimit = 0.5f;
        m_fMaxStrafeControlDist = 1.0f;
        m_fMaxPitchControlDist = 1.0f;
        m_fMaxLiftControlDist = 2.0f;
        m_fMinYawDotRatio = 0.5f;
        m_fHeightOffset = 0.0f;
    }

    static RWS::CClassFactory::CRegistrar cHelicopterControllerRegistrar(
        "cHelicopterController", cHelicopterController::MakeNew, 2240, false);
}



extern float g_fCrossLimit;         // 0x83207580

namespace VEHICLE_CONTROL
{
    Fun_Runtime::RetVal cHelicopterController::Init(const GOM::cSpawner *pSpawnArgs)
    {
        SetSpeedLimit(25.0f);
        int cur = Ret_OK;
        if (cur != cVehicleController::Init(pSpawnArgs))
            return Ret_FAIL;
        return Ret_OK;
    }

    Fun_Runtime::RetVal cHelicopterController::cHelicopterControllerPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }

    Vec4f cPointArray::GetPoint(int idx) const
    {
        const Vec4f *p;
        if (m_nCount == 0)
            p = m_aPts;
        else
        {
            int n = m_nCount;
            int i = idx % n;
            if (i < 0)
                i = i + m_nCount;
            p = &m_aPts[i];
        }
        Vec4f r;
        r.x = p->x;
        r.y = p->y;
        r.z = p->z;
        r.w = 1.0f;
        return r;
    }

    Vec3f cPointVector::GetWrapped(int idx) const
    {
        int i = idx;
        if (idx < 0)
            i = size() + idx;
        if (idx >= size())
            i -= size();
        const Vec4f *p = m_pBegin + i;
        Vec3f r;
        r.x = p->x;
        r.y = p->y;
        r.z = p->z;
        return r;
    }

    Fun_Runtime::Vec3 GetOwnerPosition(const cPosRef *ref)
    {
        return ref->m_pOwner->m_Provider.GetPosition();
    }

    template <class T> inline const T &Clamp(const T &v, const T &lo, const T &hi)
    {
        if (v > hi)
            return hi;
        if (v >= lo)
            return v;
        return lo;
    }

    float ClampedCross2D(const float *a, const float *b)
    {
        float ax = a[0];
        float ay = a[1];
        float c = b[1] * -ax + b[0] * ay;
        return Clamp(c, -g_fCrossLimit, g_fCrossLimit);
    }

    void Flatten2D(const float *in, float *out, bool normalise)
    {
        float z = in[2];
        float x = in[0];
        out[0] = x;
        out[1] = z;
        if (normalise)
        {
            if (z * z + x * x < 0.01f)
            {
                out[0] = 0.0f;
                out[1] = 0.0f;
            }
            else
            {
                float one = 1.0f;
                float s = sqrtf(x * x + z * z);
                float inv = one / s;
                out[0] = x * inv;
                out[1] = inv * z;
            }
        }
    }
}
