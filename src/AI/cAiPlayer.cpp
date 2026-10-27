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

    void cAiPlayer::SetF5F8(float v)
    {
        m_f5F8 = v;
    }

    void cAiPlayer::SetF5FC(float v)
    {
        m_f5FC = v;
    }

    int cAiPlayer::GetField60C() const
    {
        return m_field60C;
    }

    void cAiPlayer::SetField60C(int v)
    {
        m_field60C = v;
    }

    void cAiPlayer::SetS614(short v)
    {
        m_s614 = v;
    }

    unsigned char cAiPlayer::GetB616() const
    {
        return m_b616;
    }

    void cAiPlayer::SetB616(unsigned char v)
    {
        m_b616 = v;
    }

    unsigned char cAiPlayer::GetB617() const
    {
        return m_b617;
    }

    void cAiPlayer::SetB617(unsigned char v)
    {
        m_b617 = v;
    }

    int cAiPlayer::RetConstantC8()
    {
        return 0xC8;
    }
}
