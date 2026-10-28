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

    int cAiPlayer::GetField38() const
    {
        return *reinterpret_cast<const int *>((const char *)this + 0x38);
    }

    unsigned char cAiPlayer::GetByte20() const
    {
        return *reinterpret_cast<const unsigned char *>((const char *)this + 0x20);
    }

    unsigned char cAiPlayer::GetByte2E() const
    {
        return *reinterpret_cast<const unsigned char *>((const char *)this + 0x2E);
    }

    float cAiPlayer::GetFloat278() const
    {
        return *reinterpret_cast<const float *>((const char *)this + 0x278);
    }

    int cAiPlayer::GetField4E8_4() const
    {
        const unsigned int p = *reinterpret_cast<const unsigned int *>((const char *)this + 0x4E8);
        return *reinterpret_cast<const int *>((const char *)p + 0x4);
    }

    void cAiPlayer::SetFields4F8(int v, int w)
    {
        *reinterpret_cast<int *>((char *)this + 0x4F8) = v;
        *reinterpret_cast<int *>((char *)this + 0x4FC) = v;
        *reinterpret_cast<int *>((char *)this + 0x500) = w;
    }

    void *cAiPlayer::GetField5E4() const
    {
        const unsigned int p = *reinterpret_cast<const unsigned int *>((const char *)this + 0x5E4);
        if (p != 0)
            return reinterpret_cast<void *>(p - 0x1C);
        return 0;
    }

    void *cAiPlayer::GetField60() const
    {
        const unsigned int p = *reinterpret_cast<const unsigned int *>((const char *)this + 0x60);
        if (p != 0)
            return reinterpret_cast<void *>(p - 0x1C);
        return 0;
    }

    void *cAiPlayer::GetField50() const
    {
        const unsigned int p = *reinterpret_cast<const unsigned int *>((const char *)this + 0x50);
        if (p != 0)
            return reinterpret_cast<void *>(p - 0x1C);
        return 0;
    }

    const char *cAiPlayer::RetTriggerEventFlags() const
    {
        return "eTriggerEventFlags";
    }

    const char *cAiPlayer::RetEnemyStatus() const
    {
        return "eEnemyStatus";
    }

    const char *cAiPlayer::RetMapStatus() const
    {
        return "eMapStatus";
    }

    void cAiPlayer::StoreGlobal83803420()
    {
        *reinterpret_cast<int *>((char *)this) = *reinterpret_cast<const int *>(0x83803420);
    }

    int cAiPlayer::FuncEB518()
    {
        unsigned int p = *reinterpret_cast<unsigned int *>((char *)this + 0x88);
        if (p == 0)
            p = 0;
        else
            p -= 0x1C;
        const unsigned char b = *reinterpret_cast<unsigned char *>((char *)p + 0x2812);
        if (b > 1)
            return 0;
        const float f12 = *reinterpret_cast<float *>((char *)this + 0xA0);
        const float f0 = 0.0f;
        const float f13 = 10.0f;
        if (f12 >= f0 - f13)
            return 0;
        *reinterpret_cast<float *>((char *)this + 0xA0) = f0;
        return 1;
    }

    int cAiPlayer::FuncEB570()
    {
        const float f12 = *reinterpret_cast<float *>((char *)this + 0xA8);
        const float f0 = 0.0f;
        const float f13 = 3.0f;
        if (f12 >= f0 - f13)
            return 0;
        *reinterpret_cast<float *>((char *)this + 0xA8) = f0;
        return 1;
    }

    float cAiPlayer::FuncE8DC8(const void *arg) const
    {
        const char *base = (const char *)this + 0x540;
        for (unsigned int i = 0; i < 4; i++)
        {
            const char *r9 = base + (i + i * 2) * 8;
            unsigned int p = *reinterpret_cast<const unsigned int *>(r9 + 0xC);
            if (p != 0)
                p -= 0x1C;
            if (p == reinterpret_cast<unsigned int>(arg))
                return *reinterpret_cast<const float *>(r9 + 0x14);
        }
        return 0.0f;
    }
}
