#ifndef AI_CAiPLAYER_H
#define AI_CAiPLAYER_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"

namespace AI
{
    class cAiPlayer : public cNonGameBase
    {
    public:
        static const Fun_Runtime::cClass *ms_pcAiPlayerClass;

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual const char *RetClassName() const;
    };
}

#endif
