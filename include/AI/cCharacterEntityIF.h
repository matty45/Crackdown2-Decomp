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
        void *RetHeadDirection() const;
        void *RetEyePosition() const;
        float RetViewingDistance() const;
        float RetThreatObjectViewingDistance() const;
        float RetHearingAcuteness() const;
        unsigned char IsSpawnedByCrowdSystem() const;
        float RetViewingAngle() const;

        // CD2's cAiPlayer adds slot 125 (0x823E92B8) after this interface's 115..124 slots.
        virtual void vf115(); virtual void vf116(); virtual void vf117(); virtual void vf118(); virtual void vf119();
        virtual void vf120(); virtual void vf121(); virtual void vf122(); virtual void vf123(); virtual void vf124();

        // CD2: cCharacterEntityIF's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Slot52(); // 51: 0x823F0300
        virtual void Slot62(); // 61: 0x823F4828
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
