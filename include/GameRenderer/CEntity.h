// GameRenderer::CEntity (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x8265B900, from its registrar in
// CD2's initializer run); RuffKing declares the class in GameRenderer/CEntity.h with CNonEntity and defines both in
// CEntity.obj. No layout, bases or virtuals are modelled yet.
#ifndef GAMERENDERER_CENTITY_H
#define GAMERENDERER_CENTITY_H

#include "rws/attributes.h"

namespace GameRenderer
{
    class CEntity
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // GAMERENDERER_CENTITY_H
