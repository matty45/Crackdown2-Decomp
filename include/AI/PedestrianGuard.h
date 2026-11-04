// AI::PedestrianGuard (Crackdown 2): STAND-IN. Base cPedestrianBase (its inheritance registrar; the constructor
// 0x824AB1E0 calls cPedestrianBase's 0x824A91F8). Size 0x130 (its registrar).
#ifndef AI_PedestrianGuard_H
#define AI_PedestrianGuard_H

#include "AI/cPedestrianBase.h"
#include "gom/object_prototype.h"
#include "cd2/layout.h"
#include "fun_runtime/class.h"

namespace AI
{
    class PedestrianGuard : public cPedestrianBase
    {
    public:
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pPedestrianGuardClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        // CD2 0x824AB1E0, out of line (SpawnFromPrototype tail-calls it): cPedestrianBase's constructor (0x824A91F8),
        // then the words at 0x120 and 0x124 = 0.
        PedestrianGuard();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

    private:
        unsigned int m_nUnknown120; // 0x120
        unsigned int m_nUnknown124; // 0x124
        unsigned char m_pad128[0x130 - 0x128];

        CD2_LAYOUT_CHECKS(PedestrianGuard,
            CD2_SIZE(PedestrianGuard, 0x130)
            CD2_OFFSET(PedestrianGuard, m_nUnknown120, 0x120))
    };
}

#endif
