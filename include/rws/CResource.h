// STAND-IN: RWS resource interface from Burn/RuffKing; own storage remains opaque.
// CD2 cStaticEnvironment::ReCalculateResourceState (0x828093C0) calls slot 3
// for loading status; the collision-resource query (0x82808D38) calls resource slot 9.
#ifndef RWS_CRESOURCE_H
#define RWS_CRESOURCE_H
#include "fun_runtime/safedeletable.h"
#include "gom/object_prototype.h"
namespace RWS
{
    class CResource : public Fun_Runtime::cSafeDeletable
    {
    public:
        virtual ~CResource();
        virtual void AssociatePrototype(ResourceManager::cStreamingResourceClient *);
        virtual void DisassociatePrototype(ResourceManager::cStreamingResourceClient *);
        virtual eResourceLoadStatus RetLoadingStatus();
        virtual void RequestLoad(bool);
        virtual float RetPriority();
        virtual bool Create(void *, unsigned int);
        virtual bool IsStreamable();
        virtual bool Free();
        virtual const void *GetResource() const;
    protected:
        unsigned char m_unmodelled14[0x40 - 0x14];
        CD2_LAYOUT_CHECKS(CResource, CD2_SIZE(CResource, 0x40))
    };
}
#endif
