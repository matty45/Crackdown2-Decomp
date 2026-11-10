// CHARACTER::cCwCharacter (Crackdown 2): STAND-IN. Base cCharacter and the nested cCwCharacterPrototype (base
// cCharacter::cCharacterPrototype) as in RuffKing's header; CD2's inheritance registrar 0x82FAC880 names cCharacter.
// Size 0x2CE0 from its StaticCreateClass (0x8253F4D8) and class-factory registrar; its own fields are not modelled.
#ifndef CHARACTER_cCwCharacter_H
#define CHARACTER_cCwCharacter_H

#include "cd2/layout.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "CHARACTER/cCharacter.h"

namespace CHARACTER
{
    class cCwCharacter : public cCharacter
    {
    public:
        static const Fun_Runtime::cClass *ms_pcCwCharacterClass;
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 0x8253F4D8 creates the named runtime descriptor.
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        // Out of line: CD2 0x8253F570 (SpawnFromPrototype 0x8253F4A0 tail-calls it with the prototype).
        cCwCharacter(GOM::cObjectPrototype *pPrototype);
        // CD2 cReplicatedClass slot 23 (0x8253F4C0).
        virtual unsigned int GetMaxReplicatedFields() const;
        // CD2 primary slots 441/442 (0x8253F4C8/0x8253F4D0); names from Burn.
        virtual unsigned char RetReplicatedBehaviourState() const;
        virtual void ForceReplicatedBehaviourState(unsigned char nState);

        // CD2's MakeNew (0x8253F438) allocates 0x340 bytes and calls this prototype's out-of-line packet constructor
        // (0x82540068).
        class cCwCharacterPrototype : public cCharacter::cCharacterPrototype
        {
        public:
            cCwCharacterPrototype(const RWS::CAttributePacket &packet);

        private:
            unsigned char m_unmodelled330[0x340 - 0x330];

            CD2_LAYOUT_CHECKS(cCwCharacterPrototype, CD2_SIZE(cCwCharacterPrototype, 0x340))
        };

    private:
        unsigned char m_unmodelled2CC0[0x2CC8 - 0x2CC0];
    protected:
        unsigned char m_nReplicatedBehaviourState;      // 0x2CC8 (Burn 0x2B20)
    private:
        unsigned char m_unmodelled2CC9[0x2CE0 - 0x2CC9];

        CD2_LAYOUT_CHECKS(cCwCharacter,
            CD2_SIZE(cCwCharacter, 0x2CE0)
            CD2_OFFSET(cCwCharacter, m_nReplicatedBehaviourState, 0x2CC8))
    };
}

#endif
