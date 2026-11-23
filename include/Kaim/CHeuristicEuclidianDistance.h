// Kaim::CHeuristicEuclidianDistance (Crackdown 2): STAND-IN. RenderWare AI's (Kynapse) straight-line heuristic, as
// RuffKing declares it (kygraphconstraints.h). CD2's table 0x82000EF0: the deleting destructor (0x82416D68), GetCost
// (0x824055E0: the distance between the two vertices' positions, true), SetGraph (0x825FC0D8) and GetClass (0x82405620,
// returning the static Class at 0x832D9384). Every agent embeds one at +8 (AI/cAgent.h).
#ifndef KAIM_CHEURISTICEUCLIDIANDISTANCE_H
#define KAIM_CHEURISTICEUCLIDIANDISTANCE_H

#include "Kaim/CHeuristic.h"

namespace Kaim
{
    class CHeuristicEuclidianDistance : public CHeuristic
    {
    public:
        static CHeuristicClass Class;
        virtual CHeuristicClass &GetClass() const;
        virtual unsigned char GetCost(CEntity *, const CVertex &start, const CVertex &goal, float &cost);
    };
}

#endif // KAIM_CHEURISTICEUCLIDIANDISTANCE_H
