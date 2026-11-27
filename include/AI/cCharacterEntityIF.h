// AI::cCharacterEntityIF (Crackdown 2): STAND-IN, sized to CD2. cClass(0x5F1, "cCharacterEntityIF", 0x540); its
// constructor 0x823EF240 calls cCharacterInterface's (0x8254EC78). Only the accessors below are modelled;
// storage outside their observed fields remains unknown. Accessor names are the script-method names CD2 registers them
// under (`cd2.py show <address>`, "name" lines), and each field is named after its accessor: 0x823EC160/0x823EC168
// (Ret/SetMaxAiToAiVisibilityLevel) read/write the word at 0x51C; 0x823EC1F8..0x823EC230 (SetCheckTarget... and
// IsCheckingTarget...) write/read the four bytes at 0x534..0x537; 0x823EC028 (SetBulletSoundLODDeafnessEnabled) writes
// the byte at 0x539; 0x823EC038 (RetMovementType) returns the low byte of the word at 0x50C. 0x823EBF90 / 0x823EBF88
// (RetUpperbodyAnimationParams / RetFullbodyAnimationParams) return the addresses of the regions at 0x480 and 0x4B0,
// whose types are not known (byte arrays here).
// 0x823EBF38 (returns "eMovementType") and its neighbours returning enum names are slot 1 of enum registrar vtables
// that static initializers install (0x823EBF38: 0x820FBF28); their metadata interfaces are modelled separately.
// The getters returning the AIE_* registrars (0x823EC368..0x823EC890) are slot 1 of the AIE event classes' own
// tables and stay open until those classes are modelled. g_cCharacterEntityIF is named after the type CD2 registers it as (see
// AI/cAiPlayer.h); RetScriptTypeRegistration (0x823EBF28, slot 1 of the cScriptHost table 0x820FBE9C) returns it.
// m_pAIEntity (0x504; RuffKing's name and type, at 0xF8 there): cAiPlayer::RetName (0x823EB508) returns its m_name, as
// RuffKing's cAiPlayer::RetName returns m_pAIEntity's; the accessors below read the entity's script-named fields
// (AI/cCharacterEntity.h).
#ifndef AI_CCHARACTERENTITYIF_H
#define AI_CCHARACTERENTITYIF_H

#include "CHARACTER/cCharacterInterface.h"
#include "AI/cCharacterEntity.h"
#include "AI/cCharacterBrain.h"
#include "AI/cAiTargetCache.h"
#include "fun_runtime/vectorip.h"

namespace AI
{
    class cAnimParams;

    class cCharacterEntityIF : public CHARACTER::cCharacterInterface
    {
    public:
        // Reference overloads; CD2's script wrapper 0x823F0638 calls 0x822F14D8 with a local timestamp.
        bool IsVisible(cGameBase *);
        bool IsVisible(cGameBase *, float &visibilityDate);
        // CD2 script name; forwards the reference character's profile-index setter.
        void SetCharacterStateProfileFromID(unsigned int);
    private:
        unsigned char m_padC0[0x480 - 0xC0];
    protected:
        unsigned char m_upperbodyAnimationParams[0x4B0 - 0x480];
        unsigned char m_fullbodyAnimationParams[0x4E0 - 0x4B0];
    public:
        // RuffKing's member (its +0xF0, after the interface base): the NPC behaviours test their host's target info at
        // +0x4E4 and pass +0x4E0 to the cache's ClearTarget (0x8244D038) and SetTarget (0x8225CE90).
        cAiTargetCache m_TargetCache;           // 0x4E0
    private:
        unsigned char m_pad4E8[0x4F8 - 0x4E8];
    protected:
        int m_n4F8;                             // 0x4F8..0x500: written by cAiPlayer's slot 125 (0x823E92B8);
        int m_n4FC;                             // nothing names them
        int m_n500;
        cCharacterEntity *m_pAIEntity;          // 0x504
        cCharacterBrain *m_pCharacterBrain;     // 0x508
        unsigned int m_nMovementType;
    private:
        unsigned char m_pad510[0x51C - 0x510];
    protected:
        unsigned int m_nMaxAiToAiVisibilityLevel;
    private:
        unsigned char m_pad520[0x524 - 0x520];
    protected:
        void *m_pRooftopPoint;                  // 0x524: RetRooftopPoint (0x823F4E78)
    private:
        unsigned char m_pad528[0x533 - 0x528];
    public:
        // Public: cChaseBehaviour::OnEnter stores it directly (0x824CE750), as RuffKing's does.
        unsigned char m_nPerceptionOptions;     // 0x533
    protected:
        unsigned char m_bCheckingTargetTooClose;
        unsigned char m_bCheckingTargetAreaClear;
        unsigned char m_bCheckingTargetPathClear;
        unsigned char m_bCheckingTargetBlocked;
    private:
        unsigned char m_bRooftopPointSet;      // 0x538: written by SetRooftopPoint/ClearRooftopPoint; name ours
    protected:
        unsigned char m_bBulletSoundLODDeafnessEnabled;
        unsigned char m_bBreakTrafficLaws;      // 0x53A
    private:
        unsigned char m_pad53B[0x540 - 0x53B];

    public:
        static const Fun_Runtime::cClass *ms_pcCharacterEntityIFClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        // CD2 0x823EF240 is the no-argument constructor called by 0x823EBF10.
        cCharacterEntityIF();
        virtual ~cCharacterEntityIF();
        // RuffKing: cCharacterEntityIFPrototype : cCharacterInterface::cCharacterInterfacePrototype, 0x70 bytes. CD2's
        // MakeNew (0x823EBE90) allocates 0x70 bytes, calls GOM::cObjectPrototype's constructor (0x82654118) with the
        // packet and installs the vtables 0x820FBEF4 (at 0) and 0x821327A4 (at 0x18, shared by every prototype).
        class cCharacterEntityIFPrototype : public CHARACTER::cCharacterInterface::cCharacterInterfacePrototype
        {
        public:
            // __forceinline: CD2 inlines the constructor chain into MakeNew (as cCharacterInterfacePrototype's).
            __forceinline cCharacterEntityIFPrototype(const RWS::CAttributePacket &packet)
                : CHARACTER::cCharacterInterface::cCharacterInterfacePrototype(packet) {}
            // CD2: cCharacterEntityIFPrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
            // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
        public:
            virtual Fun_Runtime::RetVal Init(RWS::CAttributePacket const &); // 5: 0x823F5050
        };
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        void *RetUpperbodyAnimationParams();
        void *RetFullbodyAnimationParams();
        void *RetRooftopPoint();
        void ClearRooftopPoint(bool bClear);
        // CD2 0x823EC030 forwards to the owning AI entity's cone test.
        bool IsInViewCone(Fun_Runtime::cScriptHost *object);
        unsigned char RetMovementType() const;
        unsigned int RetCharacterState(); // CD2 script wrapper 0x823EC048 calls character slot 371.
        // CD2 script methods "AddEquipment" (0x823EC070) and "AddEquipmentDontEquip" (0x823EC0E8): the interface's
        // by-name AddEquipment, equipping or not.
        Equip::cEquipment *AddEquipment(const char *sProtoName);
        Equip::cEquipment *AddEquipmentDontEquip(const char *sProtoName);
        unsigned int RetMaxAiToAiVisibilityLevel() const;
        void SetMaxAiToAiVisibilityLevel(unsigned int value);
        void SetCheckTargetTooClose(unsigned char value);
        void SetCheckTargetAreaClear(unsigned char value);
        void SetCheckTargetPathClear(unsigned char value);
        void SetCheckTargetBlocked(unsigned char value);
        unsigned char IsCheckingTargetTooClose() const;
        unsigned char IsCheckingTargetAreaClear() const;
        unsigned char IsCheckingTargetPathClear() const;
        unsigned char IsCheckingTargetBlocked() const;
        void SetBulletSoundLODDeafnessEnabled(unsigned char value);
        // CD2 0x823EBF28: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        virtual const char *RetClassName() const;
        // CD2 0x823EBE20 / 0x823EBE30: the registered-class pair, at the start of this object's code.
        virtual const Fun_Runtime::cClass &RetClass() const;
        void *RetHeadDirection() const;
        void *RetEyePosition() const;
        float RetViewingDistance() const;
        float RetThreatObjectViewingDistance() const;
        float RetHearingAcuteness() const;
        unsigned char IsSpawnedByCrowdSystem() const;
        float RetViewingAngle() const;
        float RetHeight();
        void SetPerceptionOptions(unsigned int nPerceptionOptions);
        void SetViewingDistance(float fViewingDistance);
        void SetPlayerViewingDistance(float fViewingDistance);
        void SetThreatObjectViewingDistance(float fViewingDistance);
        void SetHearingAcuteness(float fHearingAcuteness);
        void SetViewingAngle(float fViewingAngle);
        void SetBreakTrafficLaws(unsigned char value);
        void DropImmediately();
        void ExitVehicleImmediately();
        void CrouchImmediately();
        void UncrouchImmediately();
        bool IsTryingToCrouch();
        void SetAiming(bool bAiming);
        // RuffKing's; CD2 0x823F4758 (97 callers) expands the brain's SetActiveAgent.
        void SetActiveAgent(cAgent *pState);
        // CD2 script methods: each makes the brain's agent of one type active (CreateAgent instances in this object).
        void Idle();
        void Reload(float fTolerance);
        // CD2 script methods with the parameters of RuffKing's cMoveAgent::ActivateAgent and cMoveAndFaceAgent's, but
        // the position by value as an OldVec3 (in r4/r5, as RuffKing's script method cProp::ForceSetVelocity takes it),
        // copied into a Vec3 as three floats.
        void MoveTo(Fun_Runtime::OldVec3 vecPos, bool bUsePrecision, float fStuckTimeout, float fAcceptableDistance);
        void MoveAndPrimaryFire(Fun_Runtime::OldVec3 vecPos, float fSuppressingFireTime, bool bFaceTargetWhenNotFiring,
            bool bUsePrecision, float fStuckTimeout, float fAcceptableDistance);
        void MoveAndReload(Fun_Runtime::OldVec3 vecPos, bool bUsePrecision, float fStuckTimeout,
            float fAcceptableDistance);
        void UpperBodyAnimateAndMove(Fun_Runtime::OldVec3 vecPos);
        // RuffKing's cFaceAndPrimaryFireAgent::ActivateAgent and cChaseAndPrimaryFireAgent's parameters.
        void FaceAndPrimaryFire(float fSuppressingFireTime, float fTolerance, float fFirePauseTime, float fMinTargetDistance,
            float fMaxTargetDistance);
        void ChaseAndPrimaryFire(float fSuppressingFireTime, bool bFaceTargetWhenNotFiring, float fAcceptableDistance,
            float fTargetTooFarDistance, Fun_Runtime::Vec3 vGuardPoint, float fGuardDistance);
        void Chase(bool bUseDefendedPosition, cGameBase *pDefendedObject, Fun_Runtime::OldVec3 vecDefendedPosition,
            float fRadius);
        void ResetIntelliFleeTimeout();
        void SetIntelliFleeUpperBodyAnim(bool bUse, int nAnimID);
        void SetIntelliFleeLookBehindAnim(bool bUse, int nLookAnimID, int nTurnAnimID, float fMinTime, float fMaxTime);
        void SetIntelliFleeCowerAnim(int nStartAnimID, int nLoopAnimID, int nEndAnimID);
        void SetIntelliFleePanicAnim(int nAnimID);
        void SetWanderFleeAvoidPosition(const Fun_Runtime::OldVec3 &vPosition);
        void SetWanderFleeAvoidObject(cGameBase *pObject);
        void SetWanderFleeUpperBodyAnim(bool bUse, int nAnimID);
        void SetWanderFleeLookBehindAnim(bool bUse, int nLookAnimID, int nTurnAnimID, float fMinTime, float fMaxTime);
        void Follow(float fMinDistance, float fMaxDistance);
        // RuffKing's cReactionAgent::ActivateAgent parameters; CD2's copy (0x823F2A40, four callers) is this object's.
        void Reaction(const Fun_Runtime::Vec3 &vReactionPos, char nReaction, unsigned int nReactionFlags,
            float fReactionChance, Fun_Runtime::Vec3 *pReactionSourceVelo);
        void SafeDistancePrimaryFire(float fDistance, float fFirePauseTime, bool bFiringEnabled,
            bool bFaceTargetWhenNotFiring);
        void ProtectPosition(float fRadius, Fun_Runtime::OldVec3 vPosition, float fSuppressingFireTime);
        void ClearBrainState();
        void CloseAttack(float fTime);
        void ProtectObject(float fRadius, cGameBase *pObject, float fSuppressingFireTime);
        void Brake(bool bBrakeFlag, float fStopSpeed);
        // RuffKing's cFaceAgent::ActivateAgent with a point; CD2's copy (0x823F43B8, four callers) is this object's.
        void Face(float fTolerance, const Fun_Runtime::OldVec3 &vPointToFace);
        void Circle(float fDistance, bool bAdjustMovement, bool bLockDirection, float fTimeout);
        // CD2 script method "SetMovementType" (0x823F3650): stores m_nMovementType and sets the character's speeds.
        void SetMovementType(unsigned char nMovementType);
        void BackAway(bool bAdjustMovement, float fSafeDistance, float fTooCloseDistance);
        void Dodge(bool bFiringEnabled, bool bFaceTargetWhenNotFiring);
        void MoveAndFace(Fun_Runtime::OldVec3 vecPos, bool bUsePrecision, float fStuckTimeout, float fAcceptableDistance);
        void PrimaryFire(float fTolerance);
        void SecondaryFire(float fTolerance);
        void Throw(float fTolerance);
        void UpperBodyAnimateAndFace();
        void StoreItem();
        void PickUpItem();
        void PickUp();
        void Drop();
        void Crouch();
        void Uncrouch();
        void ExitVehicle();
        void Face(float fTolerance);
        void ChaseAndReload();
        void Intercept();
        // RuffKing's cAmbientTrafficDrivingAgent::ActivateAgent(entity, nInitialEdge, false) and
        // cFleeingDangerAgent::ActivateAgent(entity, vDangerPosition), as cChaseBehaviour's EnterDrivingTraffic and
        // EnterDriveFleeing call them; CD2's copies (0x823F1610, 0x823F16E8) are this object's. The names are ours.
        void ActivateAmbientTrafficDrivingAgent(unsigned int nInitialEdge, bool bFlag);
        void ActivateFleeingDangerAgent(const Fun_Runtime::Vec3 &vDangerPosition);
        // RuffKing's cCharacterInterface::PlayGenericFullBodyAnimation(nAnimID, nFlags); CD2's (0x823F2DB0, seven
        // callers) reads the full-body animation parameters at 0x4B0.., so it is this class's.
        void PlayGenericFullBodyAnimation(int nAnimID, unsigned int nFlags);
        // RuffKing's cFullBodyAnimateAgent::ActivateAgent(entity, nAnimID, nFlags, ...), as FreakBase::STATE_Enter_Detonate
        // calls it with 0x1B59F and 0x14; CD2's copy (0x823F2F90, four callers) is this object's. The name is ours.
        void ActivateFullBodyAnimateAgent(int nAnimID, unsigned int nFlags);
        // RuffKing's cAmbientAnimAgent::ActivateAgent(entity, aParams, ...), as FreakBase::OnAmbient calls it; CD2's copy
        // (0x823F3290, five callers) is this object's and takes the parameters only. The name is ours.
        void ActivateAmbientAnimAgent(const Fun_Runtime::cVectorip<cAnimParams *, 10> &aParams);

        // CD2's cAiPlayer adds slot 125 (0x823E92B8) after this interface's 115..124 slots.
        virtual void vf115(); virtual void vf116(); virtual void vf117(); virtual void vf118(); virtual void vf119();
        // 120, 122 and 123 are named by the script methods "IsTrafficClear", "RetRadius" and "IsVehicleOperable",
        // whose registered addresses are this class's vcall thunks for those slots (0x823FCBC8, 0x823FCBF0, 0x823FCBB8).
        virtual bool IsTrafficClear(); virtual void vf121(); virtual float RetRadius(); virtual bool IsVehicleOperable();
        virtual void vf124();

        // CD2: cCharacterEntityIF's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void SetGameImportance(eGameImportance nGI); // 51: 0x823F0300
        virtual bool IsAIEntityOwner(Kaim::CEntity *pEntity); // 61: 0x823F4828
        virtual void vf75(); // 75: 0x8224C0C0
        virtual void vf76(); // 76: 0x82360140
        virtual void vf80(); // 80: 0x823EF740
        virtual void vf81(); // 81: 0x823EF860
        virtual void vf87(); // 87: 0x823F0230
        virtual void vf90(); // 90: 0x823F0180
        virtual bool ForceIntoVehicle(Vehicle::cVehicle *,unsigned int); // 100: 0x823F46C0
        virtual bool ForceOutOfVehicle(); // 101: 0x823F46D0
        virtual void vf105(); // 105: 0x823F0260
        virtual void vf106(); // 106: 0x823F02B0
        virtual bool IsA(Fun_Runtime::cClass const &) const; // cRegisteredClass 1: 0x8222FC18
    public:
        CD2_LAYOUT_CHECKS(cCharacterEntityIF,
            CD2_SIZE(cCharacterEntityIF, 0x540)
            CD2_OFFSET(cCharacterEntityIF, m_upperbodyAnimationParams, 0x480)
            CD2_OFFSET(cCharacterEntityIF, m_fullbodyAnimationParams, 0x4B0)
            CD2_OFFSET(cCharacterEntityIF, m_TargetCache, 0x4E0)
            CD2_OFFSET(cCharacterEntityIF, m_n4F8, 0x4F8)
            CD2_OFFSET(cCharacterEntityIF, m_pAIEntity, 0x504)
            CD2_OFFSET(cCharacterEntityIF, m_pCharacterBrain, 0x508)
            CD2_OFFSET(cCharacterEntityIF, m_nPerceptionOptions, 0x533)
            CD2_OFFSET(cCharacterEntityIF, m_bBreakTrafficLaws, 0x53A)
            CD2_OFFSET(cCharacterEntityIF, m_nMovementType, 0x50C)
            CD2_OFFSET(cCharacterEntityIF, m_nMaxAiToAiVisibilityLevel, 0x51C)
            CD2_OFFSET(cCharacterEntityIF, m_bCheckingTargetTooClose, 0x534)
            CD2_OFFSET(cCharacterEntityIF, m_bCheckingTargetAreaClear, 0x535)
            CD2_OFFSET(cCharacterEntityIF, m_bCheckingTargetPathClear, 0x536)
            CD2_OFFSET(cCharacterEntityIF, m_bCheckingTargetBlocked, 0x537)
            CD2_OFFSET(cCharacterEntityIF, m_bBulletSoundLODDeafnessEnabled, 0x539)
            CD2_OFFSET(cCharacterEntityIF, m_pRooftopPoint, 0x524))
    };
}

#endif // AI_CCHARACTERENTITYIF_H
