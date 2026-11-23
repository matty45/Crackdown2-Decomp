// Kaim::CObject (Crackdown 2): STAND-IN. RenderWare AI's (Kynapse) root class: RuffKing declares only a virtual
// destructor (slot 0) and class-specific operator new/delete on the Kaim allocator. CD2's deleting destructor of
// CHeuristicEuclidianDistance (0x82416D68) restores this class's table (0x820FCCD8, one slot) and nothing else, so the
// destructor is user-declared and inline here. The allocation operators are not modelled.
#ifndef KAIM_COBJECT_H
#define KAIM_COBJECT_H

namespace Kaim
{
    class CObject
    {
    public:
        CObject() {}
        virtual ~CObject() {}
    };
}

#endif // KAIM_COBJECT_H
