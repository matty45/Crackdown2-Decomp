#ifndef CHARACTER_CCHARACTERVFXPROFILE_H
#define CHARACTER_CCHARACTERVFXPROFILE_H

#include "rws/attributes.h"
#include "editor/guid_event_handler.h"
#include "cd2/layout.h"

namespace CHARACTER
{
    class cCharacterVFXProfile : public RWS::CAttributeHandler
    {
    public:
        static const char *const pcCharacterVFXProfileClassID;

        cCharacterVFXProfile(const RWS::CAttributePacket &packet);

        virtual const char *RetClassName() const;

        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        unsigned char m_pad[0x104];
        Editor::cGUIDEventHandler<cCharacterVFXProfile> m_EventHandler;
        // CD2: cCharacterVFXProfile's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x82555538
    };
}

#endif // CHARACTER_CCHARACTERVFXPROFILE_H
