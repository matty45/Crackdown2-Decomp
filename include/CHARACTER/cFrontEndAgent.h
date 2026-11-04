#include "gom/object_prototype.h"
#include "rws/attributes.h"
// CHARACTER::cFrontEndAgent (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8289CF68) builds cClass(0x67D, "cFrontEndAgent", 0x3EC0); 0x3EC0 is the size its registrar gives.
#ifndef CHARACTER_CFRONTENDAGENT_H
#define CHARACTER_CFRONTENDAGENT_H

#include "fun_runtime/class.h"
#include "CHARACTER/cCwTransCharacter.h"

namespace CHARACTER
{
    class cFrontEndAgent
    {
    public:
        // RuffKing's cPlayerCharacterPrototype is CD2's cCwTransCharacterPrototype.
        // CD2 MakeNew calls 0x82312E00 and installs 0x82162A20; slot 5 is Init.
        class cFrontEndAgentPrototype : public cCwTransCharacter::cCwTransCharacterPrototype
        {
        public:
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        };
        // CD2 0x8289CE58: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x8289CF38: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x83022E88 names placement factory 0x8289cf48.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcFrontEndAgentClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // CHARACTER_CFRONTENDAGENT_H
