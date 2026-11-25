// AI::cPathObjectOwner (Crackdown 2): STAND-IN. RuffKing's class (rw/ai/include/graph/kypathobject.h) is 24 bytes: a
// vptr, the path object and the local graph info, and 11 virtuals; its destructor is not virtual and out of line (CD2
// 0x82405D60, which cHingedDoor's destructor 0x827446B0 calls). CD2's class is 0x28 bytes: cHingedDoor's constructor
// (0x82744560) builds it inline at 0xEB0 (the vptr, then zero in the nine words after it), and the class ends
// cHingedDoor at 0xEB0 + 0x28 (0xEE0, its registered size) and cSlidingDoor at 0xED0 + 0x28 (0xF00). The last four
// words are not in RuffKing; their names are ours.
// CD2's table for it is 0x820FCEDC, 11 slots, in RuffKing's order: CreatePathObject 0x82405DC0, DestroyPathObject
// 0x82405E60, GetCost 0x824066B8, GoTo 0x82405EF8, InitStreamingGraphs 0x824062F8, TermStreamingGraphs 0x82406388;
// GetPathObjectInput, CanGoFromTo and UpdateEdgeInGraph hold the shared "return 1" body (RuffKing defines
// GetPathObjectInput inline), OnEnterGraph and OnExitGraph the shared empty body. cHingedDoor's OnEnterGraph
// (0x82744808) passes the owning body to LinkIntersectingGraphEdges (0x82405F00) as its second argument.
#ifndef AI_CPATHOBJECTOWNER_H
#define AI_CPATHOBJECTOWNER_H

#include "cd2/layout.h"

namespace Fun_Runtime { class Vec3; }
namespace PHYSICS { class cBody; }
namespace Kaim
{
    class CEntity;
    class CEdge;
    class CConstraint;
    class CVector;
    class CAction;
    class CSpatialGraph;
}

namespace AI
{
    class cPathObject;
    class cStreamingGraph;
    class TStreamingCallbackFunctor;

    class cPathObjectOwner
    {
    public:
        cPathObjectOwner() : m_pPathObject(0), m_nUnknown18(0), m_nUnknown1C(0), m_nUnknown20(0), m_nUnknown24(0) {}
        ~cPathObjectOwner();

        virtual bool CreatePathObject();
        virtual void DestroyPathObject();
        virtual unsigned char GetPathObjectInput();
        virtual unsigned char GetCost(Kaim::CEntity *, Kaim::CEdge &, Kaim::CConstraint &, float &);
        virtual unsigned char CanGoFromTo(Kaim::CEntity &, const Kaim::CVector &, const Kaim::CVector &);
        virtual unsigned char GoTo(Kaim::CEntity &bot, const Kaim::CVector &dest, Kaim::CAction &action,
                                   unsigned char &hasArrived, Kaim::CVector &targetPoint);
        virtual unsigned char UpdateEdgeInGraph(Kaim::CSpatialGraph &);
        virtual void InitStreamingGraphs(const Fun_Runtime::Vec3 &vecPosition);
        virtual void TermStreamingGraphs();
        virtual void OnEnterGraph(cStreamingGraph *pStreamingGraph);
        virtual void OnExitGraph(cStreamingGraph *);

    protected:
        void LinkIntersectingGraphEdges(cStreamingGraph *pStreamingGraph, PHYSICS::cBody *pBody);

        class cStreamingGraphInfo
        {
        public:
            cStreamingGraphInfo() : m_pOwner(0), m_pStreamingGraph(0), m_pStreamedInFunctor(0), m_pStreamedOutFunctor(0) {}

        private:
            cPathObjectOwner *m_pOwner;                     // 0x0
            cStreamingGraph *m_pStreamingGraph;             // 0x4
            TStreamingCallbackFunctor *m_pStreamedInFunctor;    // 0x8
            TStreamingCallbackFunctor *m_pStreamedOutFunctor;   // 0xC
        };

        cPathObject *m_pPathObject;                         // 0x4
        cStreamingGraphInfo m_LocalGraphInfo;               // 0x8
        unsigned int m_nUnknown18;
        unsigned int m_nUnknown1C;
        unsigned int m_nUnknown20;
        unsigned int m_nUnknown24;

        CD2_LAYOUT_CHECKS(cPathObjectOwner,
            CD2_SIZE(cPathObjectOwner, 0x28)
            CD2_OFFSET(cPathObjectOwner, m_pPathObject, 0x4)
            CD2_OFFSET(cPathObjectOwner, m_LocalGraphInfo, 0x8))
    };
}

#endif // AI_CPATHOBJECTOWNER_H
