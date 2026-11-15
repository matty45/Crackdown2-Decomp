// Kaim::CEntityAttribute (Crackdown 2): STAND-IN. RenderWare AI's (Kynapse) entity-attribute base; RuffKing's
// CEntityWidth and CEntityHeight derive from it, with a virtual destructor and their value at +4. Its virtuals beyond
// the destructor are not modelled.
#ifndef KAIM_CENTITYATTRIBUTE_H
#define KAIM_CENTITYATTRIBUTE_H

namespace Kaim
{
    class CEntityAttribute
    {
    public:
        virtual ~CEntityAttribute();
    };
}

#endif // KAIM_CENTITYATTRIBUTE_H
