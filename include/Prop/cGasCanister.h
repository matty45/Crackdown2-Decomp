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
        CD2_LAYOUT_CHECKS(cGasCanister,
            CD2_SIZE(cGasCanister, 0xE40)
            CD2_OFFSET(cGasCanister, m_nCState, 0xE30)
            CD2_OFFSET(cGasCanister, m_fRocketTimer, 0xE34)
            CD2_OFFSET(cGasCanister, m_nNumKillsForLocalPlayer, 0xE38)
            CD2_OFFSET(cGasCanister, m_bFuseAudioPlayed, 0xE3C))
    };
}

#endif // PROP_CGASCANISTER_H
