// Kaim::CHeuristic (Crackdown 2): STAND-IN. RenderWare AI's (Kynapse) path-cost heuristic, 8 bytes, as RuffKing
// declares it (kygraphconstraints.h): GetCost (slot 1, pure), the inline SetGraph (slot 2; CD2 0x825FC0D8 stores its
// argument at +4) and GetClass (slot 3, pure), with m_graph at +4. CD2's agent constructors store 0 to +4 of the
// embedded heuristic after its derived vptr.
#ifndef KAIM_CHEURISTIC_H
#define KAIM_CHEURISTIC_H

#include "Kaim/CObject.h"
#include "cd2/layout.h"

namespace Kaim
{
    class CEntity;
    class CVertex;
    class CSpatialGraph;
    class CHeuristicClass;

    class CHeuristic : public CObject
    {
    public:
        virtual unsigned char GetCost(CEntity *, const CVertex &, const CVertex &, float &) = 0;
        virtual void SetGraph(CSpatialGraph *graph) { m_graph = graph; }
        virtual CHeuristicClass &GetClass() const = 0;

    protected:
        CHeuristic() : m_graph(0) {}

        CSpatialGraph *m_graph;     // 0x4

        CD2_LAYOUT_CHECKS(CHeuristic,
            CD2_SIZE(CHeuristic, 0x8)
            CD2_OFFSET(CHeuristic, m_graph, 0x4))
    };
}

#endif // KAIM_CHEURISTIC_H
