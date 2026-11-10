#include "fun_runtime/class.h"
#include "rws/attributes.h"
// Prop::cGasCanister (Crackdown 2): STAND-IN for the class name only. Base Prop::cProp, as in RuffKing's header;
// RetClassName (0x827437F8) is slot 11 of the vtable at 0x8200E520, as cNonGameBase's RetClassName.
#ifndef PROP_CGASCANISTER_H
#define PROP_CGASCANISTER_H

#include "Prop/cProp.h"

namespace Prop
{
    class cGasCanister : public Prop::cProp
    {
    public:
        static const Fun_Runtime::cClass *ms_pcGasCanisterClass;
        // CD2 placement factory 0x82743808 tail-calls constructor 0x82743828.
        cGasCanister(GOM::cObjectPrototype *);
        static Fun_Runtime::cClass &StaticCreateClass(); // CD2 0x822709A0
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual Fun_Runtime::RetVal Term();
        virtual void NotifyDetonation(cGameBase *, CHARACTER::cCharacterInterface *, unsigned char);
        // RuffKing field names; CD2 constructor 0x82743828 establishes these offsets.
        enum eCanisterState { CS_FULL_O_GAS, CS_ROCKET, CS_DEPLETED };
    private:
        eCanisterState m_nCState;
        float m_fRocketTimer;
        unsigned int m_nNumKillsForLocalPlayer;
        bool m_bFuseAudioPlayed;
        // CD2: cGasCanister's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual bool EnterPhysicalState(); // 7: 0x8272A070
        virtual void Slot23(); // 23: 0x8226CB58
        virtual void Slot64(); // 63: 0x82743DB0
        virtual void vf76(); // 76: 0x827439E0
        virtual void vf127(); // 127: 0x82743988
        virtual void vf330(); // 330: 0x8288FB78
        virtual void vf331(); // 331: 0x8288FB78
        virtual Fun_Runtime::cClass const & RetClass() const; // cBody 0: 0x82744240
        virtual bool IsA(Fun_Runtime::cClass const &) const; // cBody 1: 0x82744248
        virtual void ReplicateInitialFields(); // cReplicatedClass 8: 0x82743E78
        virtual void ReplicateFields(); // cReplicatedClass 9: 0x82743EB8
    private:
        CD2_LAYOUT_CHECKS(cGasCanister,
            CD2_SIZE(cGasCanister, 0xE40)
            CD2_OFFSET(cGasCanister, m_nCState, 0xE30)
            CD2_OFFSET(cGasCanister, m_fRocketTimer, 0xE34)
            CD2_OFFSET(cGasCanister, m_nNumKillsForLocalPlayer, 0xE38)
            CD2_OFFSET(cGasCanister, m_bFuseAudioPlayed, 0xE3C))
    };
}

#endif // PROP_CGASCANISTER_H
