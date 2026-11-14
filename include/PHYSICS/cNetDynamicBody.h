#include "fun_runtime/class.h"
// STAND-IN: RuffKing hierarchy; CD2 subobjects at 0, 0x420 and 0x510; cProp interfaces start at 0x7A0.
#ifndef CD2_PHYSICS_CNETDYNAMICBODY_H
#define CD2_PHYSICS_CNETDYNAMICBODY_H
#include "PHYSICS/cDynamicBody.h"
#include "Network/cPositionalProxy.h"
#include "Network/cReplicatedClass.h"
#include "fun_runtime/vec3.h"
#include "fun_runtime/quat.h"
namespace PHYSICS
{
    class cNetDynamicBody : public cDynamicBody, public cPositionalProxy, public cReplicatedClass
    {
    public:
        // RuffKing's ownership arbitration result and its non-virtual arbiter (CD2 0x826881E8, which cVehicle's
        // ArbitrateOwnership 0x826DEF78 falls back to).
        enum eArbitrationResult
        {
            eAR_ThisNodeWon = 0,
            eAR_ThisNodeLost,
        };
        eArbitrationResult ArbitrateOwnership(unsigned char nNodeID, unsigned int TimeStamp);
        // CD2 initializer 0x82FDFC60 calls this class's descriptor factory.
        static const Fun_Runtime::cClass *ms_pcNetDynamicBodyClass;
        // CD2 0x82687E38 creates the named runtime descriptor.
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual ~cNetDynamicBody();
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual bool IsSequential() const;
        virtual bool IsOwnedLocally();
        virtual void SetPingedFieldStatesForNode(unsigned char);
        virtual SNetworkHeader::etNetworkDataType GetReplicatedObjectType() const;
        virtual unsigned int GetMaxReplicatedFields() const;
        virtual void ReplicateInitialFields(); // cReplicatedClass 8: 0x826886C0
        virtual void ReplicateFields(); // cReplicatedClass 9: 0x82688780
        virtual void SkipDefaultReplicatedFields(); // cReplicatedClass 11: 0x82688540
        // Primary overrides: the slots where CD2's cNetDynamicBody table (0x82131E80) differs from cDynamicBody's
        // (0x8200D058); names and signatures are the bases'.
        virtual Fun_Runtime::RetVal Init(GOM::cSpawner const *);               // 18: 0x826880A0
        virtual Fun_Runtime::RetVal Reinitialise(GOM::cSpawner const *);       // 38: 0x82688148
        virtual Fun_Runtime::RetVal TermForReuse();                            // 39: 0x82688198
        virtual void Slot64();                                                 // 63: 0x82689C78
        virtual void vf76();                                                   // 76: 0x822D0950
        virtual void vf134();                                                  // 134: 0x82457A38
        virtual void vf158();                                                  // 158: 0x82689BF0
        virtual void vf254();                                                  // 254: 0x822C5A30
        virtual void vf299();                                                  // 299: 0x822CA060
        virtual void vf301();                                                  // 301: 0x822C9FF0
        // Primary slots 304..313: cNetDynamicBody's own virtuals. CD2's cNetDynamicBody table (0x82131E80, stored by
        // the constructor 0x82687ED0) has 314 slots. Names and signatures are RuffKing's (its 12 own virtuals in this
        // order, without OnContingencyDepenetration and OnInitReplication): cVehicle's EndInterpolationOptional and
        // UpdateNetworkInterpolation bodies (0x826DAA40, 0x826DC888) are RuffKing's.
        virtual void EndInterpolationOptional(); virtual void ProcessDynamicObjectTerm(unsigned char nNodeID, bool bForceDelete); virtual void UpdateNetworkInterpolation(float dt, bool bEnableNewInterp); virtual void ActivateNetworkInterpolation(const Fun_Runtime::Vec3 &vTargetInterpolationPosition, const Fun_Runtime::Quat &qTargetInterpolationOrientation, bool bEnableNewInterp); virtual bool GetReplicatedPhysicalState(); virtual void SetDeletingReason(char);
        virtual char GetDeletingReason(); virtual void SetUpForReplication(unsigned int nID); virtual void ProxyFixupActivator(); virtual void ProxyFixupCarryingCharacter();
    private:
        unsigned char m_unknown740[0x770 - 0x740];
    protected:
        // RuffKing's name, 0x20 bytes below its offset as the fields around it; cVehicle's EndInterpolationOptional
        // (0x826DAA40) clears it.
        bool m_bNetworkInterpolationActive;     // 0x770
    private:
        unsigned char m_unknown771[0x7A0 - 0x771];
        CD2_LAYOUT_CHECKS(cNetDynamicBody,
            CD2_SIZE(cNetDynamicBody, 0x7A0)
            CD2_OFFSET(cNetDynamicBody, m_bNetworkInterpolationActive, 0x770))
    };
}
#endif
