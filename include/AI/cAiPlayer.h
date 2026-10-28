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
        unsigned char _pad7C[0x88 - 0x7C];
    protected:
        unsigned int m_field88;
        unsigned char _pad8C[0xA0 - 0x8C];
        float m_fA0;
        unsigned char _padA4[0xA8 - 0xA4];
        float m_fA8;
        unsigned char _padAC[0x278 - 0xAC];
        float m_f278;
        unsigned char _pad27C[0x4E8 - 0x27C];
        unsigned int m_field4E8;
        unsigned char _pad4EC[0x4F8 - 0x4EC];
        int m_field4F8;
        int m_field4FC;
        int m_field500;
        unsigned char _pad504[0x540 - 0x504];
        unsigned char _pad540[0x5A0 - 0x540];

        unsigned char _pad5A0[0x5E4 - 0x5A0];
        unsigned int m_field5E4;
        unsigned char _pad5E8[0x5F8 - 0x5E8];
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
        int GetField38() const;
        unsigned char GetByte20() const;
        unsigned char GetByte2E() const;
        float GetFloat278() const;
        int GetField4E8_4() const;
        void SetFields4F8(int v, int w);
        void *GetField5E4() const;
        void *GetField60() const;
        void *GetField50() const;
        const char *RetTriggerEventFlags() const;
        const char *RetEnemyStatus() const;
        const char *RetMapStatus() const;
        void StoreGlobal83803420();
        int FuncEB518();
        int FuncEB570();
        float FuncE8DC8(const void *p) const;
    };
}

#endif
