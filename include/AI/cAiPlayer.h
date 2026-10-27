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

    private:
        unsigned char _pad0[0x5F8 - 0x7C];
    protected:
        float m_f5F8;
        float m_f5FC;
        unsigned char _pad1[0x60C - 0x600];
        int m_field60C;
        unsigned char _pad2[0x614 - 0x610];
        short m_s614;
        unsigned char m_b616;
        unsigned char m_b617;

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual const char *RetClassName() const;
    public:
        void SetF5F8(float v);
        void SetF5FC(float v);
        int GetField60C() const;
        void SetField60C(int v);
        void SetS614(short v);
        unsigned char GetB616() const;
        void SetB616(unsigned char v);
        unsigned char GetB617() const;
        void SetB617(unsigned char v);
        static int RetConstantC8();
    };
}

#endif
