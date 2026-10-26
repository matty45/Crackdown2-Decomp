#ifndef AI_PEDESTRIAN_H
#define AI_PEDESTRIAN_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"

namespace AI
{
    class Pedestrian : public cNonGameBase
    {
    public:
        static const Fun_Runtime::cClass *ms_pcPedestrianClass;

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    };
}

#endif
