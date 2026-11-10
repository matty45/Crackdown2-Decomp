#ifndef VFX_cLinkedVFXPrototype_H
#define VFX_cLinkedVFXPrototype_H

#include "rws/attributes.h"
#include "VFX/cAmbientVFXSpawner.h"

namespace VFX
{
    // RuffKing names the ambient-prototype base; CD2 0x827FA478 initializes
    // its 0x30 bytes and the GUID handler at +0x30, for a total size of 0x44.
    class cLinkedVFXPrototype : public cAmbientVFXPrototypeBase
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        __forceinline cLinkedVFXPrototype(const RWS::CAttributePacket &packet) : cAmbientVFXPrototypeBase(packet) {}
        // CD2 0x827FA568 restores this table before GUID cleanup and the base's table after it.
        virtual ~cLinkedVFXPrototype() {}
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual const char *RetClassName() const;

        Editor::cGUIDEventHandler<cLinkedVFXPrototype> m_EventHandler;

        CD2_LAYOUT_CHECKS(cLinkedVFXPrototype,
            CD2_SIZE(cLinkedVFXPrototype, 0x44)
            CD2_OFFSET(cLinkedVFXPrototype, m_EventHandler, 0x30))
    };
}

#endif
