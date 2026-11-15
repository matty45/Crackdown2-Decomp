// STAND-IN: RuffKing's standalone water-phantom interface and 0x70-byte layout.
// CD2 water-zone phantom code accesses its parent's pointer immediately after this base, at +0x70.
#ifndef PHYSICS_CSHAPEPHANTOMBODYWATER_H
#define PHYSICS_CSHAPEPHANTOMBODYWATER_H
#include "PHYSICS/cOBBox.h"
#include "fun_runtime/retval.h"
class cGameBase;
namespace PHYSICS
{
    class cCustomAabbPhantomWater;
    __declspec(align(16)) class cShapePhantomBodyWater
    {
    public:
        virtual ~cShapePhantomBodyWater();
        virtual Fun_Runtime::RetVal Init(const cOBBox &, unsigned int);
        virtual Fun_Runtime::RetVal Term();
        virtual void Update();
        virtual void UpdateTransform(const Fun_Runtime::Mtx &);
        virtual void AddToWorld();
        virtual void RemoveFromWorld();
        virtual bool IsInited() const;
        virtual void OnGameObjectEnter(cGameBase *);
        virtual void OnGameObjectLeave(cGameBase *);
    protected:
        virtual void OnGameObjectInside(cGameBase *);
        virtual bool IsValidObject(cGameBase *);
    private:
        // Own storage is opaque: this wrapper needs only the complete base size and virtual interface.
        unsigned char m_unmodelled4[0x70 - 4];
        CD2_LAYOUT_CHECKS(cShapePhantomBodyWater, CD2_SIZE(cShapePhantomBodyWater, 0x70))
    };
}
#endif
