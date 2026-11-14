// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "ZoneManager/cVOAZone.h"
#include "cd2/memory.h"
#include "SaveGame/cLoadStream.h"
#include "SaveGame/cSaveStream.h"

// The narrow-string assign instantiation belongs to another translation unit (CD2 0x82438A70): keep it external, so
// that the LTCG model does not specialize its offset and count arguments away.
extern template std::basic_string<char, std::char_traits<char>, Fun_Runtime::cAllocator<char> > &
    std::basic_string<char, std::char_traits<char>, Fun_Runtime::cAllocator<char> >::assign(
        const std::basic_string<char, std::char_traits<char>, Fun_Runtime::cAllocator<char> > &, size_t, size_t);

namespace ZoneManager
{
    static const char *const pcVOAZoneClassID = "cVOAZone";

    RWS::CAttributeHandler *cVOAZone::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cVOAZone(packet);
    }

    const char *cVOAZone::RetClassName() const
    {
        return "cVOAZone";
    }

    cVOAZone::~cVOAZone()
    {
    }

    void cVOAZone::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cPlayerTriggerZone::HandleAttributes(packet);
        for (RWS::CAttributeCommandIterator it(packet, pcVOAZoneClassID); !it.IsFinished(); ++it)
        {
            switch (it->GetCommandId())
            {
            case 0:
                m_strName = it->GetAs_char_ptr();
                break;
            }
        }
        if (packet.IsInstanceCreationPacket())
            InitTriggerZone();
    }

    void cVOAZone::Load(SaveGame::cLoadStream *stream)
    {
        bool initialised = true;
        stream->ReadBool(initialised);
        if (initialised)
        {
            if (!IsInitialised())
                InitTriggerZone();
        }
        else if (IsInitialised())
            TermTriggerZone();
    }

    void cVOAZone::Save(SaveGame::cSaveStream *stream)
    {
        stream->WriteBool(IsInitialised());
    }

    static RWS::CClassFactory::CRegistrar cVOAZoneRegistrar(
        "cVOAZone", cVOAZone::MakeNew, 0x100, false);
}
