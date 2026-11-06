#include "rws/classfactory.h"
#include "unknown/cHunterGathererGameModePrototype.h"
#include "cd2/memory.h"

namespace unknown
{
    const char *cHunterGathererGameModePrototype::RetClassName() const
    {
        return "cHunterGathererGameModePrototype";
    }

    static RWS::CClassFactory::CRegistrar cHunterGathererGameModePrototypeRegistrar(
        "cHunterGathererGameModePrototype", cHunterGathererGameModePrototype::MakeNew, 0x198, false);

    // CD2 0x8287E1E8: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cHunterGathererGameModePrototype::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cHunterGathererGameModePrototype;
    }
    float cHunterGathererGameModePrototype::RetFloat148() const
    {
        return m_fParameter148;
    }

    float cHunterGathererGameModePrototype::RetFloat14C() const
    {
        return m_fParameter14C;
    }

    float cHunterGathererGameModePrototype::RetFloat150() const
    {
        return m_fParameter150;
    }

    bool cHunterGathererGameModePrototype::RetFlag154() const
    {
        return m_bParameter154;
    }

    bool cHunterGathererGameModePrototype::RetFlag155() const
    {
        return m_bParameter155;
    }

    bool cHunterGathererGameModePrototype::RetFlag174() const
    {
        return m_bParameter174;
    }

    float cHunterGathererGameModePrototype::RetFloat178() const
    {
        return m_fParameter178;
    }

    float cHunterGathererGameModePrototype::RetFloat17C() const
    {
        return m_fParameter17C;
    }

    cHunterGathererGameModePrototype::cHunterGathererGameModePrototype()
        : m_bParameter174(true)
    {
        // CD2 stores this flag before the tuning fields; vptr scheduling is still unmatched.
        m_fParameter148 = 15.0f;
        m_fParameter14C = 10.0f;
        m_fParameter178 = 3.0f;
        m_bParameter154 = false;
        m_fParameter17C = 0.8f;
        m_bParameter155 = false;
        m_fParameter190 = 0.5f;
        m_nParameter18C = 5;
    }

    int cHunterGathererGameModePrototype::RetStringID() const
    {
        return 0x5416C5C3;
    }

    int cHunterGathererGameModePrototype::RetEffectID(unsigned int index) const
    {
        return m_aEffectIDs[index];
    }

}
