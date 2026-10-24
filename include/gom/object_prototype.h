// GOM::cObjectPrototype: the prototype (spawn template) every game class's prototype derives from, and its
// ResourceManager::cStreamingResourceClient base. Bases and size (0x70) from the RuffKing and Burn PDBs; confirmed in CD2:
// - the constructor (0x82654118) takes only the packet (Burn's signature; RuffKing adds a bool) and stores this
//   class's vptrs at 0 (0x8212CEE8) and 0x18 (0x821327A4);
// - every prototype chain reaches that constructor (chase, flocket and helicopter prototypes, the last directly);
// - 0x821327A4 is also every derived prototype's vtable at 0x18: none overrides the client's virtuals, so the linker
//   folded the identical copies (config/symbol_aliases.txt).
// The client's vtable has 8 slots in CD2 where the PDBs have 6. Slots 0-2 and 5-7 carry RuffKing's names in RuffKing's
// order (slot 2's body tests the resource-state byte as HasLoadedResources does; slots 5 and 6 are empty); slots 3 and
// 4 are CD2's and unnamed. Field layout differs between RuffKing and Burn; only the resource-state byte is placed from
// CD2's code.
#ifndef GOM_OBJECT_PROTOTYPE_H
#define GOM_OBJECT_PROTOTYPE_H

#include "rws/attributes.h"
#include "cd2/layout.h"

enum eResourcesType { };
enum eResourceLoadStatus { };

namespace RWS { class CResource; }

namespace ResourceManager
{
    class cStreamingResourceClient
    {
    protected:
        float m_fStreamingPriority;
        float m_fRenderStreamingPriority;

    public:
        cStreamingResourceClient();
        virtual bool RequestResources(eResourcesType, bool);
        virtual eResourceLoadStatus CheckResources(eResourcesType);
        virtual bool HasLoadedResources(eResourcesType);
        virtual void Slot3();
        virtual void Slot4();
        virtual void NotifyResourceUnload(RWS::CResource &);
        virtual void NotifyResourceLoaded(RWS::CResource &);
        virtual void ReCalculateResourceState();

        CD2_LAYOUT_CHECKS(cStreamingResourceClient,
            CD2_SIZE(cStreamingResourceClient, 0xC))
    };
}

namespace GOM
{
    class cObjectPrototype : public RWS::CAttributeHandler, public ResourceManager::cStreamingResourceClient
    {
    private:
        unsigned char m_pad24[0x44 - 0x24];
        unsigned char m_nResourceState;   // 0x44: HasLoadedResources (0x82655540) tests it
        unsigned char m_pad45[0x70 - 0x45];

    public:
        cObjectPrototype(const RWS::CAttributePacket &);
        virtual ~cObjectPrototype();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual void PropagateAttributes();
        virtual bool HandleDataInNewDesignBuild();
        virtual bool RequestResources(eResourcesType, bool);
        virtual eResourceLoadStatus CheckResources(eResourcesType);
        virtual bool HasLoadedResources(eResourcesType);
        virtual void Slot3();
        virtual void Slot4();
        virtual void NotifyResourceUnload(RWS::CResource &);
        virtual void NotifyResourceLoaded(RWS::CResource &);
        virtual void ReCalculateResourceState();

        CD2_LAYOUT_CHECKS(cObjectPrototype,
            CD2_SIZE(cObjectPrototype, 0x70)
            CD2_OFFSET(cObjectPrototype, m_nResourceState, 0x44))
    };
}

#endif // GOM_OBJECT_PROTOTYPE_H
