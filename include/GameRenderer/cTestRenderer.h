// GameRenderer::cTestRenderer (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x82667848, from its registrars in CD2's
// initializer run); RuffKing names the class in cTestRenderer.obj. No layout or virtuals are modelled yet.
#ifndef GAMERENDERER_CTESTRENDERER_H
#define GAMERENDERER_CTESTRENDERER_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace GameRenderer
{
    class cTestRenderer
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // GAMERENDERER_CTESTRENDERER_H
