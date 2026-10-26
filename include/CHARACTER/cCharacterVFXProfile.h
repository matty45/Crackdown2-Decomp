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
    };
}

#endif // CHARACTER_CCHARACTERVFXPROFILE_H
