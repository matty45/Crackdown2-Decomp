#include "gom/object_prototype.h"
#include "rws/attributes.h"
// CHARACTER::cFrontEndAgent (Crackdown 2): STAND-IN: base from its inheritance registrar; own fields not modelled yet.
// StaticCreateClass (0x8289CF68) builds cClass(0x67D, "cFrontEndAgent", 0x3EC0); 0x3EC0 is the size its registrar gives.
#ifndef CHARACTER_CFRONTENDAGENT_H
#define CHARACTER_CFRONTENDAGENT_H

#include "fun_runtime/class.h"
#include "CHARACTER/cCwTransCharacter.h"

namespace CHARACTER
{
    // Base from CD2's inheritance registrar (cFrontEndAgent under cCwTransCharacter); size 0x3EC0 from its registrar.
    class cFrontEndAgent : public cCwTransCharacter
    {
    public:
        // RuffKing's cPlayerCharacterPrototype is CD2's cCwTransCharacterPrototype.
        // CD2 MakeNew calls 0x82312E00 and installs 0x82162A20; slot 5 is Init.
        // CD2's MakeNew (0x8289CEC8) allocates 0x460, calls cCwTransCharacterPrototype's constructor (0x82312E00) and
        // stores this class's vptrs: the constructor is inline and adds no fields.
        class cFrontEndAgentPrototype : public cCwTransCharacter::cCwTransCharacterPrototype
        {
        public:
            __forceinline cFrontEndAgentPrototype(const RWS::CAttributePacket &packet)
                : cCwTransCharacter::cCwTransCharacterPrototype(packet) {}
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);

            // CD2: cFrontEndAgentPrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
            // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
        public:
            virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x82539220
        public:
            CD2_LAYOUT_CHECKS(cFrontEndAgentPrototype,
                CD2_SIZE(cFrontEndAgentPrototype, 0x460))
        };
        // CD2 0x8289CE58: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x8289CF38: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x83022E88 names placement factory 0x8289cf48.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 0x8289D010: the placement factory (0x8289CF48) calls it out of line with the prototype.
        cFrontEndAgent(GOM::cObjectPrototype *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcFrontEndAgentClass;
        static Fun_Runtime::cClass &StaticCreateClass();

    private:
        // Own fields are not recovered.
        unsigned char m_unmodelled2E00[0x3EC0 - 0x2E00];

        CD2_LAYOUT_CHECKS(cFrontEndAgent,
            CD2_SIZE(cFrontEndAgent, 0x3EC0))
    };
}

#endif // CHARACTER_CFRONTENDAGENT_H
