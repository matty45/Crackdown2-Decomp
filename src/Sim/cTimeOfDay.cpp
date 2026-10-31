#include "Sim/cTimeOfDay.h"

unsigned char g_838518A0;     // global at 0x838518A0
unsigned char g_83851758;     // global at 0x83851758
unsigned char g_8385177C;     // global at 0x8385177C
unsigned char g_838517A0;     // global at 0x838517A0

namespace Sim
{
    void *cTimeOfDay::GetPtr838518A0() const
    {
        return &g_838518A0;
    }

    void *cTimeOfDay::GetPtr83851758() const
    {
        return &g_83851758;
    }

    void *cTimeOfDay::GetPtr8385177C() const
    {
        return &g_8385177C;
    }

    void *cTimeOfDay::GetPtr838517A0() const
    {
        return &g_838517A0;
    }
}
