#include "AI/cAiPlayer.h"

namespace AI
{
    const Fun_Runtime::cClass *cAiPlayer::ms_pcAiPlayerClass = 0;

    const Fun_Runtime::cClass &cAiPlayer::RetClass() const
    {
        return *ms_pcAiPlayerClass;
    }

    const char *cAiPlayer::RetClassName() const
    {
        return "cAiPlayer";
    }
}
