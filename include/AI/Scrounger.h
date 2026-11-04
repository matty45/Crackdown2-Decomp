// AI::Scrounger (Crackdown 2): STAND-IN. Base FreakBase (its inheritance registrar; the constructor 0x824BABB0
// calls FreakBase's 0x824ABD60). Size 0x130 (its registrar).
#ifndef AI_Scrounger_H
#define AI_Scrounger_H

#include "AI/FreakBase.h"
#include "gom/object_prototype.h"
#include "cd2/layout.h"
#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace AI
{
    class Scrounger : public FreakBase
    {
    public:
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pScroungerClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        // CD2 0x824BABB0, out of line (SpawnFromPrototype tail-calls it): FreakBase's constructor (0x824ABD60), then
        // the word at 0x120 = 13.
        Scrounger();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

    private:
        unsigned int m_nUnknown120; // 0x120
        unsigned char m_pad124[0x130 - 0x124];

        CD2_LAYOUT_CHECKS(Scrounger,
            CD2_SIZE(Scrounger, 0x130)
            CD2_OFFSET(Scrounger, m_nUnknown120, 0x120))
    };
}

#endif
