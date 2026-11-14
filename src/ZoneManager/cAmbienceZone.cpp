// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "ZoneManager/cAmbienceZone.h"
#include "cd2/memory.h"
#include "rw/rwmem.h"

// The wide-string assign instantiation belongs to another translation unit (CD2 0x82438418): keep it external, so that
// the LTCG model does not specialize its offset and count arguments away.
extern template std::basic_string<wchar_t, std::char_traits<wchar_t>, Fun_Runtime::cAllocator<wchar_t> > &
    std::basic_string<wchar_t, std::char_traits<wchar_t>, Fun_Runtime::cAllocator<wchar_t> >::assign(
        const std::basic_string<wchar_t, std::char_traits<wchar_t>, Fun_Runtime::cAllocator<wchar_t> > &, size_t, size_t);

namespace ZoneManager
{
    static const char *const pcAmbienceZoneClassID = "cAmbienceZone";

    RWS::CAttributeHandler *cAmbienceZone::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cAmbienceZone(packet);
    }

    const char *cAmbienceZone::RetClassName() const
    {
        return "cAmbienceZone";
    }

    cAmbienceZone::~cAmbienceZone()
    {
    }

    void cAmbienceZone::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cPlayerTriggerZone::HandleAttributes(packet);
        for (RWS::CAttributeCommandIterator it(packet, pcAmbienceZoneClassID); !it.IsFinished(); ++it)
        {
            switch (it->GetCommandId())
            {
            case 0:
                m_strName = it->GetAs_char_ptr();
                break;
            case 1:
                m_bIndoor = rwSwap32(it->GetAs_UInt32()) != 0;
                break;
            }
        }
        InitTriggerZone();
    }

    static RWS::CClassFactory::CRegistrar cAmbienceZoneRegistrar(
        "cAmbienceZone", cAmbienceZone::MakeNew, 0x100, false);
}
