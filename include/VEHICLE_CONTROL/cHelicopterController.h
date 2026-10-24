// VEHICLE_CONTROL::cHelicopterController: AI helicopter flight controller (CD2 object size 0x8C0).
// CD2 layout, worked out from F36 (ctor), F29/F30/F32, F35 and the base ctor F09 (0x82781B38):
//   0x000 cVehicleController (size 0x840, STAND-IN, see below)
//   0x840 m_fMaxSpeed  0x844 m_fDefaultMaxSpeed (copied from the vehicle's physics data)  0x848 m_iCurrentWaypoint
//   0x84C..0x88B tuning floats  0x88C..0x88E bools  0x890 m_nFullSimMode  0x8A0 Vec3 m_vTarget  0x8B0 Vec3 m_vTargetHeading
// RuffKing's class is 0x900 with fields from 0x870; CD2's is smaller, field names are RuffKing's matched by position.
// Bases: cVehicleController is a cNonGameBase (gom/non_game_base.h; its constructor F09, 0x82781B38, calls cNonGameBase's)
// with fields from 0x7C; its own virtuals start at slot 68. Named from CD2's helicopter vtable (0x8200AB38): AssignVehicle
// (69), SetSpeedLimit (76), GetSpeedLimit (77), ResetSpeedLimit (78); RuffKing declares all four in cVehicleController.
// The rest are placeholders vfN. Its Term is inline: CD2 emits it out of line at 0x82781CF0 (cNonGameBase::Term, then
// that file's Ret_OK) and inlines it into the helicopter's Term. Prototypes derive from GOM::cObjectPrototype.
// Vehicle::cVehicle: polymorphic interface at +0x30 (slot 1 = type test), physics data pointer at +0x1948.
#ifndef VEHICLE_CONTROL_CHELICOPTERCONTROLLER_H
#define VEHICLE_CONTROL_CHELICOPTERCONTROLLER_H

#include "rws/attributes.h"
#include "cd2/layout.h"
#include "fun_runtime/class.h"
#include "fun_runtime/vec3.h"
#include "fun_runtime/retval.h"
#include "gom/non_game_base.h"

namespace Fun_Runtime
{
}

namespace Vehicle
{
    class cVehiclePhysics { public: unsigned char m_pad[872]; float m_fMaxSpeed; };
    class cVehicleRoot { public: virtual void vf0(); unsigned char m_pad[0x2C]; };
    class cVehicleIface
    {
    public:
        virtual void vf0();
        virtual bool IsKindOf(int tag);
        unsigned char m_pad[0x1914];
        cVehiclePhysics *m_pPhysics;
    };
    class cVehicle : public cVehicleRoot, public cVehicleIface {};
}

namespace VEHICLE_CONTROL
{
    class cVehicleController : public cNonGameBase
    {
    public:
        // RuffKing: cVehicleControllerPrototype : cNonGameBase::cNonGameBasePrototype (: GOM::cObjectPrototype).
        // Its destructor is out of line (CD2 0x82783498); prototype destructors of derived controllers call it.
        class cVehicleControllerPrototype : public GOM::cObjectPrototype
        {
        public:
            __forceinline cVehicleControllerPrototype(const RWS::CAttributePacket &packet) : GOM::cObjectPrototype(packet) {}
            virtual ~cVehicleControllerPrototype();
        };

        cVehicleController();
        virtual Fun_Runtime::RetVal Init(const GOM::cSpawner *);   // 0x82245930
        virtual Fun_Runtime::RetVal Term()
        {
            cNonGameBase::Term();
            return Ret_OK;
        }
        // own virtuals, slots 68..95
        virtual void vf68();
        virtual void AssignVehicle(Vehicle::cVehicle *);
        virtual void vf70();
        virtual void vf71();
        virtual void vf72();
        virtual void vf73();
        virtual void vf74();
        virtual void vf75();
        virtual void SetSpeedLimit(float);
        virtual float GetSpeedLimit();
        virtual void ResetSpeedLimit();
        virtual void vf79();
        virtual void vf80();
        virtual void vf81();
        virtual void vf82();
        virtual void vf83();
        virtual void vf84();
        virtual void vf85();
        virtual void vf86();
        virtual void vf87();
        virtual void vf88();
        virtual void vf89();
        virtual void vf90();
        virtual void vf91();
        virtual void vf92();
        virtual void vf93();
        virtual void vf94();
        virtual void vf95();
        bool m_bFlag7C;
        bool m_bFlag7D;
        unsigned char m_pad7E[10];
        void *m_pVehicleRaw;     // 0x88
        unsigned char m_pad8C[8];
        Vehicle::cVehicle *m_pVehicle; // 0x94
        unsigned char m_pad98[0x7A8];
    };


    // Plain vectors (no constructor), as returned by value through a hidden pointer.
    struct Vec4f { float x, y, z, w; };
    struct Vec3f { float x, y, z; };

    // Stand-in: fixed array of 96 points plus a count at 0x600 (F42).
    class cPointArray
    {
    public:
        Vec4f m_aPts[96];
        unsigned short m_nCount;
        Vec4f GetPoint(int idx) const;
    };

    // Stand-in: vector of 16-byte points, begin/end at +4/+8 (F48).
    class cPointVector
    {
    public:
        void *m_pAlloc;
        Vec4f *m_pBegin;
        Vec4f *m_pEnd;
        int size() const { return (int)(m_pEnd - m_pBegin); }
        Vec3f GetWrapped(int idx) const;
    };

    // Stand-in for an object with a position provider at +28 (F47).
    class cPosProvider { public: virtual void vf0(); virtual void vf1(); virtual void vf2(); virtual Fun_Runtime::Vec3 GetPosition(); };
    class cPosOwner { public: unsigned char m_pad[28]; cPosProvider m_Provider; };
    class cPosRef { public: void *m_pad; cPosOwner *m_pOwner; };
    Fun_Runtime::Vec3 GetOwnerPosition(const cPosRef *ref);

    float ClampedCross2D(const float *a, const float *b);
    void Flatten2D(const float *in, float *out, bool normalise);

    class cHelicopterController : public cVehicleController
    {
    public:
        class cHelicopterControllerPrototype : public cVehicleControllerPrototype
        {
        public:
            __forceinline cHelicopterControllerPrototype(const RWS::CAttributePacket &packet) : cVehicleControllerPrototype(packet) {}
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);   // slot 5 of its vtable (0x8214C1A8)
        };

        enum etHelicopterFullSimMode { HFSM_0, HFSM_1, HFSM_2, HFSM_3, HFSM_4 };

        float m_fMaxSpeed;                  // 0x840
        float m_fDefaultMaxSpeed;           // 0x844
        int m_iCurrentWaypoint;             // 0x848
        float m_fMinControlCalcDist;        // 0x84C
        float m_fMinYawCalcDist;            // 0x850
        float m_fStrafeControlCapability;   // 0x854
        float m_fPitchControlCapability;    // 0x858
        float m_fLiftControlCapability;     // 0x85C
        float m_fYawControlCapability;      // 0x860
        float m_fCubicFractionalLookahead;  // 0x864
        float m_fMinLookAhead;              // 0x868
        float m_fMaxLookAhead;              // 0x86C
        float m_fLookaheadTweak;            // 0x870
        float m_fYawOnlyNoThrustLimit;      // 0x874
        float m_fMaxStrafeControlDist;      // 0x878
        float m_fMaxPitchControlDist;       // 0x87C
        float m_fMaxLiftControlDist;        // 0x880
        float m_fMinYawDotRatio;            // 0x884
        float m_fHeightOffset;              // 0x888
        bool m_bTransitionToPhysicalWhenPossible; // 0x88C
        bool m_bTransitionToSimpleWhenPossible;   // 0x88D
        bool m_bMaintainHeadingInSimple;          // 0x88E
        int m_nFullSimMode;                 // 0x890
        bool m_bDrawControlDebug;
        bool m_bDrawRouteDebug;
        Fun_Runtime::Vec3 m_vTarget;        // 0x8A0
        Fun_Runtime::Vec3 m_vTargetHeading; // 0x8B0

        static const char *const pcHelicopterControllerClassID;

        cHelicopterController();
        virtual const char *RetClassName() const;
        virtual Fun_Runtime::RetVal Term();
        virtual Fun_Runtime::RetVal Init(const GOM::cSpawner *);
        virtual void SetSpeedLimit(float);
        virtual float GetSpeedLimit();
        virtual void ResetSpeedLimit();
        virtual void AssignVehicle(Vehicle::cVehicle *);

        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static cHelicopterController *SpawnFromPrototype(GOM::cObjectPrototype *, void *);

        CD2_LAYOUT_CHECKS(cHelicopterController,
            CD2_SIZE(cHelicopterController, 0x8C0)
            CD2_OFFSET(cHelicopterController, m_pVehicle, 0x94)
            CD2_OFFSET(cHelicopterController, m_fMaxSpeed, 0x840)
            CD2_OFFSET(cHelicopterController, m_bTransitionToPhysicalWhenPossible, 0x88C)
            CD2_OFFSET(cHelicopterController, m_nFullSimMode, 0x890)
            CD2_OFFSET(cHelicopterController, m_vTarget, 0x8A0)
            CD2_OFFSET(cHelicopterController, m_vTargetHeading, 0x8B0))
    };
}

#endif


