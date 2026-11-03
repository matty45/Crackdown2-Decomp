#ifndef VFX_cScatterMeshResources_H
#define VFX_cScatterMeshResources_H

#include "rws/attributes.h"

namespace VFX
{
    // STAND-IN: CD2 MakeNew (0x827AA2A8) allocates 0x1C and clears the pointer at 0x18.
    // The resource-pointer name is ours; the pointed-to type is not yet recovered.
    class cScatterMeshResources : public RWS::CAttributeHandler
    {
    public:
        cScatterMeshResources() : m_pResources(0) {}
        // CD2's deleting wrapper 0x827AB180 stores the derived vptr.
        virtual ~cScatterMeshResources() {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
    private:
        void *m_pResources;
        CD2_LAYOUT_CHECKS(cScatterMeshResources,
            CD2_SIZE(cScatterMeshResources, 0x1C)
            CD2_OFFSET(cScatterMeshResources, m_pResources, 0x18))
    };
}

#endif
