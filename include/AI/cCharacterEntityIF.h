// AI::cCharacterEntityIF (Crackdown 2): STAND-IN, sized to CD2. cClass(0x5F1, "cCharacterEntityIF", 0x540); its
// constructor 0x823EF240 calls cCharacterInterface's (0x8254EC78). Only the accessors below are modelled;
// storage outside their observed fields remains unknown. Accessor names are the script-method names CD2 registers them
// under (`cd2.py show <address>`, "name" lines), and each field is named after its accessor: 0x823EC160/0x823EC168
// (Ret/SetMaxAiToAiVisibilityLevel) read/write the word at 0x51C; 0x823EC1F8..0x823EC230 (SetCheckTarget... and
// IsCheckingTarget...) write/read the four bytes at 0x534..0x537; 0x823EC028 (SetBulletSoundLODDeafnessEnabled) writes
// the byte at 0x539; 0x823EC038 (RetMovementType) returns the low byte of the word at 0x50C. 0x823EBF90 / 0x823EBF88
// (RetUpperbodyAnimationParams / RetFullbodyAnimationParams) return the addresses of the regions at 0x480 and 0x4B0,
// whose types are not known (byte arrays here).
// RetMovementTypeEnum (0x823EBF38, returns "eMovementType") has no script name: the name is ours. It is slot 1 of the
// registrar vtable 0x820FBF28, like cAiPlayer's RetMapStatus. The g_ globals are named after the types CD2 registers
// them as (see AI/cAiPlayer.h); the GetPtr getters' own names are not known.
// m_pAIEntity (0x504; RuffKing's name and type, at 0xF8 there): cAiPlayer::RetName (0x823EB508) returns its m_name, as
// RuffKing's cAiPlayer::RetName returns m_pAIEntity's; the accessors below read the entity's script-named fields
// (AI/cCharacterEntity.h).
#ifndef AI_CCHARACTERENTITYIF_H
#define AI_CCHARACTERENTITYIF_H

#include "CHARACTER/cCharacterInterface.h"
#include "AI/cCharacterEntity.h"

namespace AI
{
    class cCharacterEntityIF : public CHARACTER::cCharacterInterface
    {
    private:
        unsigned char m_padC0[0x480 - 0xC0];
    protected:
        unsigned char m_upperbodyAnimationParams[0x4B0 - 0x480];
        unsigned char m_fullbodyAnimationParams[0x4F8 - 0x4B0];
        int m_n4F8;                             // 0x4F8..0x500: written by cAiPlayer's slot 125 (0x823E92B8);
        int m_n4FC;                             // nothing names them
        int m_n500;
        cCharacterEntity *m_pAIEntity;          // 0x504
        unsigned char m_pad508[0x50C - 0x508];
        unsigned int m_nMovementType;
    private:
        unsigned char m_pad510[0x51C - 0x510];
    protected:
        unsigned int m_nMaxAiToAiVisibilityLevel;
    private:
        unsigned char m_pad520[0x534 - 0x520];
    protected:
        unsigned char m_bCheckingTargetTooClose;
        unsigned char m_bCheckingTargetAreaClear;
        unsigned char m_bCheckingTargetPathClear;
        unsigned char m_bCheckingTargetBlocked;
    private:
        unsigned char m_pad538;
    protected:
        unsigned char m_bBulletSoundLODDeafnessEnabled;
    private:
        unsigned char m_pad53A[0x540 - 0x53A];

    public:
        static const Fun_Runtime::cClass *ms_pcCharacterEntityIFClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        // CD2 0x823EF240 is the no-argument constructor called by 0x823EBF10.
        cCharacterEntityIF();
        virtual ~cCharacterEntityIF();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        void *RetUpperbodyAnimationParams();
        void *RetFullbodyAnimationParams();
        unsigned char RetMovementType() const;
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
        void *GetPtrcCharacterEntityIF() const;
        void *GetPtrAIE_OBJECT_APPROACHING() const;
        void *GetPtrAIE_EJECTED_FROM_VEHICLE() const;
        void *GetPtrAIE_TARGETED() const;
        void *GetPtrAIE_INTERESTING_OBJECT() const;
        void *GetPtrAIE_INTERESTING_OBJECT_BASIC_REACTION() const;
        void *GetPtrAIE_DAMAGE_TAKEN() const;
        void *GetPtrAIE_DIED() const;
        void *GetPtrAIE_EQUIPMENT_LOST() const;
        void *GetPtrAIE_CARRIED_OBJECT_LOST() const;
        void *GetPtrAIE_SET_ON_FIRE() const;
        void *GetPtrAIE_END_FIRE() const;
        void *GetPtrAIE_TOUCHED() const;
        void *GetPtrAIE_TOUCHED_GRENADE() const;
        virtual const char *RetClassName() const;
        const char *RetMovementTypeEnum() const;
        const char *RetPerceptionOptions() const;
        const char *RetFaceTarget() const;
        const char *RetAttackState() const;
        const char *RetState() const;
        void *RetHeadDirection() const;
        void *RetEyePosition() const;
        float RetViewingDistance() const;
        float RetThreatObjectViewingDistance() const;
        float RetHearingAcuteness() const;
        unsigned char GetBool38_50() const;
        unsigned char IsSpawnedByCrowdSystem() const;
        float RetViewingAngle() const;

        CD2_LAYOUT_CHECKS(cCharacterEntityIF,
            CD2_SIZE(cCharacterEntityIF, 0x540)
            CD2_OFFSET(cCharacterEntityIF, m_upperbodyAnimationParams, 0x480)
            CD2_OFFSET(cCharacterEntityIF, m_fullbodyAnimationParams, 0x4B0)
            CD2_OFFSET(cCharacterEntityIF, m_n4F8, 0x4F8)
            CD2_OFFSET(cCharacterEntityIF, m_pAIEntity, 0x504)
            CD2_OFFSET(cCharacterEntityIF, m_nMovementType, 0x50C)
            CD2_OFFSET(cCharacterEntityIF, m_nMaxAiToAiVisibilityLevel, 0x51C)
            CD2_OFFSET(cCharacterEntityIF, m_bCheckingTargetTooClose, 0x534)
            CD2_OFFSET(cCharacterEntityIF, m_bCheckingTargetAreaClear, 0x535)
            CD2_OFFSET(cCharacterEntityIF, m_bCheckingTargetPathClear, 0x536)
            CD2_OFFSET(cCharacterEntityIF, m_bCheckingTargetBlocked, 0x537)
            CD2_OFFSET(cCharacterEntityIF, m_bBulletSoundLODDeafnessEnabled, 0x539))
    };
}

#endif // AI_CCHARACTERENTITYIF_H
