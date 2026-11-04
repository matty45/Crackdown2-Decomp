#include "rws/attributes.h"
// CHARACTER::cFrontEndAgent (Crackdown 2): STAND-IN. Base cCwTransCharacter (its inheritance registrar); fields not modelled.
// StaticCreateClass (0x8289CF68) builds cClass(0x67D, "cFrontEndAgent", 0x3EC0); 0x3EC0 is the size its registrar gives.
#ifndef CHARACTER_CFRONTENDAGENT_H
#define CHARACTER_CFRONTENDAGENT_H

#include "fun_runtime/class.h"
#include "CHARACTER/cCwTransCharacter.h"
#include "gom/object_prototype.h"
#include "cd2/layout.h"

namespace CHARACTER
{
    class cFrontEndAgent : public cCwTransCharacter
    {
    public:
        virtual const char *RetClassName() const;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcFrontEndAgentClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        // Out of line: CD2 0x8289D010 (SpawnFromPrototype tail-calls it with the prototype).
        cFrontEndAgent(GOM::cObjectPrototype *prototype);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);

    private:
        unsigned char m_unmodelled2E00[0x3EC0 - 0x2E00];

        CD2_LAYOUT_CHECKS(cFrontEndAgent, CD2_SIZE(cFrontEndAgent, 0x3EC0))
    };
}

#endif // CHARACTER_CFRONTENDAGENT_H
